#!/bin/bash

# Create the directories
mkdir -p Logos/src/connectors
mkdir -p Logos/src/utils
mkdir -p Logos/include/connectors
mkdir -p Logos/include/utils
mkdir -p Logos/tests
mkdir -p Logos/docs
mkdir -p Logos/config

# Create the source files
touch Logos/src/main.c
touch Logos/src/engine.c
touch Logos/src/connectors/chatgpt_driver.c
touch Logos/src/connectors/google_ai_driver.c
touch Logos/src/connectors/grok_driver.c
touch Logos/src/utils/http_utils.c
touch Logos/src/utils/json_utils.c

# Create the header files
touch Logos/include/engine.h
touch Logos/include/connectors/chatgpt_driver.h
touch Logos/include/connectors/google_ai_driver.h
touch Logos/include/connectors/grok_driver.h
touch Logos/include/utils/http_utils.h
touch Logos/include/utils/json_utils.h

# Create the test files
touch Logos/tests/test_engine.c
touch Logos/tests/test_chatgpt_driver.c

# Create the documentation file
touch Logos/docs/README.md

# Create the config file
touch Logos/config/api_config.h

# Create the Makefile
touch Logos/Makefile

echo "Directory structure and files created successfully!"

