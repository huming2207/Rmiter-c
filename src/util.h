//
// Created by Ming Hu on 8/5/17.
//

#ifndef RMITER_C_UTIL_H
#define RMITER_C_UTIL_H

// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>

// libcurl HTTP library (must be installed first)
#include <curl/curl.h>

// cJSON JSON library
#include "../cJSON/cJSON.h"

// Google Gumbo HTML parsing library
#include <gumbo.h>

// string operations
#define NULL_CHAR_SPACE 1
#define NEWLINE_CHAR_SPACE 1
#define EXTRA_CHARS_SPACE (NULL_CHAR_SPACE + NEWLINE_CHAR_SPACE)

// Curl parameters
#define CHROME_USER_AGENT "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36 "
#define RMITER_USER_AGENT "rmiter-c/1.0"
#define FULL_USER_AGENT CHROME_USER_AGENT RMITER_USER_AGENT

// Debug flag
#define RMITER_DEBUG_CURL 1

typedef struct curl_string
{
    char * string;
    size_t size;
} CurlString;


void clean_unused_input();

char * get_user_input(int length);

int str_to_int(char * str);

CURL * get_rmiter_curl(char * url);

static size_t save_response_to_string(void *contents, size_t size, size_t nmemb, CurlString * userp);

bool file_exist(char * file_path);

void get_password( char *pw, size_t pwsize);

#endif //RMITER_C_UTIL_H
