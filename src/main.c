#include <stdio.h>
#include <stdlib.h>

#include "chatgpt_driver.h"

int main() {
    const char *api_key = "sk-xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxA";  // Set your API key
    const char *message = "Hello, ChatGPT!";

    char *response = send_message_to_chatgpt(api_key, message);
    if (response) {
        printf("Response from ChatGPT: %s\n", response);
        free(response);  // Free the response data
    }

    return 0;
}

