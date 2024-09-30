#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON.h"
#include "chatgpt_driver.h"

// Structure for storing response data
struct response_data {
    char *data;
    size_t size;
};

// Callback function for writing response data
size_t WriteCallback(void *contents, size_t size, size_t nmemb, struct response_data *userp) {
    size_t total_size = size * nmemb;
    userp->data = realloc(userp->data, userp->size + total_size + 1);
    if (userp->data == NULL) {
        fprintf(stderr, "Not enough memory for response data\n");
        return 0;
    }
    memcpy(&(userp->data[userp->size]), contents, total_size);
    userp->size += total_size;
    userp->data[userp->size] = '\0';  // Null-terminate the string
    return total_size;
}

// Function to send a message to ChatGPT
char *send_message_to_chatgpt(const char *api_key, const char *message) {
    CURL *curl;
    CURLcode res;

    struct response_data chunk = {NULL, 0};  // Initialize response data

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        // Set the URL and headers
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", api_key);
        headers = curl_slist_append(headers, auth_header);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Create JSON payload
        cJSON *json_payload = cJSON_CreateObject();
        cJSON *messages = cJSON_CreateArray();
        cJSON *message_obj = cJSON_CreateObject();
        cJSON_AddStringToObject(message_obj, "role", "user");
        cJSON_AddStringToObject(message_obj, "content", message);
        cJSON_AddItemToArray(messages, message_obj);
        cJSON_AddItemToObject(json_payload, "messages", messages);
        cJSON_AddStringToObject(json_payload, "model", "gpt-3.5-turbo");  // Specify the model

        // Set the JSON payload
        char *json_str = cJSON_Print(json_payload);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_str);

        // Set the write callback function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        // Perform the request
        res = curl_easy_perform(curl);

        // Clean up
        cJSON_Delete(json_payload);
        free(json_str);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            free(chunk.data);
            return NULL;
        }
    }
    curl_global_cleanup();

    return chunk.data;  // Return the response
}

