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

// libcurl HTTP library (must be installed first)
#include <curl/curl.h>

// cJSON JSON library
#include "../cJSON/cJSON.h"

// Google Gumbo HTML parsing library
#include <gumbo.h>

#define NULL_CHAR_SPACE 1
#define NEWLINE_CHAR_SPACE 1
#define EXTRA_CHARS_SPACE (NULL_CHAR_SPACE + NEWLINE_CHAR_SPACE)

void clean_unused_input();

char * get_user_input(int length);

int str_to_int(char * str);

#endif //RMITER_C_UTIL_H
