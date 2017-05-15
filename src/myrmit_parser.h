//
// Created by Ming Hu on 8/5/17.
//

#ifndef RMITER_C_MYRMIT_PARSER_H
#define RMITER_C_MYRMIT_PARSER_H

#include "util.h"

// CAS login interface specified details
#define RMIT_SSO_CAS_URL "https://sso-cas.rmit.edu.au/rmitcas/login"
#define RMIT_SSO_CAS_POST_REFFERER RMIT_SSO_CAS_URL
#define CHROME_USER_AGENT "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36 "
#define RMITER_USER_AGENT "rmiter-c/1.0"
#define FULL_USER_AGENT CHROME_USER_AGENT RMITER_USER_AGENT

// Debug flag
#define RMITER_DEBUG_CURL 1


typedef struct curl_string
{
    char * string;
    int size;
} CurlString;

void run_cas_init(char * user_name, char * user_password, char * cookie_path);

const char * get_init_token(char * cookie_file_path);

static size_t save_response_to_string(void *contents, size_t size, size_t nmemb, void *userp);

const char * parse_login_ticket(char * raw_html);

const char * find_login_ticket(GumboNode * current_node);

#endif //RMITER_C_MYRMIT_PARSER_H
