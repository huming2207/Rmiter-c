//
// Created by Ming Hu on 8/5/17.
//



#include "util.h"

void clean_unused_input()
{
    char c_char;
    while(c_char = (char)fgetc(stdin), c_char != EOF && c_char != '\n')
    { } /* Gobble each character. */

    /* Reset the error status of the stream. */
    clearerr(stdin);
}

char * get_user_input(int length)
{
    /** Initialize something (of course), cast to size_t because CLion warning sucks. */
    char * user_input;
    user_input = malloc((size_t)(length + EXTRA_CHARS_SPACE));

    printf("Enter your command: ");

    /** If user inputs nothing or some issues happens, return NULL to terminate the process */
    if(user_input == NULL)
    {
        return NULL;
    }

    /** Do fgets to grab input */
    fgets(user_input, length, stdin);

    /** If it's not ended with new line character, then it must be overflowed */
    if(user_input[strlen(user_input) - 1] != '\n')
    {
        clean_unused_input();
        return NULL;
    }

    /** Append a null character */
    strcat(user_input, "\0");

    /** Do a trick to remove the new line character */
    user_input = strtok(user_input, "\n");

    return user_input;
}

int str_to_int(char * str)
{
    /** Get (only) the first int found from str */
    long num = strtol(str, NULL, 10);

    /** Return int, detect overflow before conversion */
    if(num > INT_MIN && num < INT_MAX)
    {
        return ((int)num);
    }
    else
    {

        return -32767;
    }
}

CURL * get_rmiter_curl(char * url)
{
    // Curl declaration
    CURL * curl;

    // Curl init
    curl = curl_easy_init();

    // Detect if it successfully initialized
    if(curl == NULL)
    {
        printf("[ERROR] libCurl init failed!\n");
        exit(1);
    }


#ifdef RMITER_DEBUG_CURL

    // Set debug mode
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

#endif

    // Set Curl parameters
    // Set SSO CAS login server URL
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // Set User Agent
    curl_easy_setopt(curl, CURLOPT_USERAGENT, FULL_USER_AGENT);

    // Set write function pointer (see libcurl's example)
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save_response_to_string);

    return curl;

}

// Came from libCurl example: https://curl.haxx.se/libcurl/c/getinmemory.html
static size_t save_response_to_string(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t real_size = size * nmemb;
    CurlString * string_mem = (CurlString *)userp;

    string_mem->string = realloc(string_mem->string, string_mem->size + real_size + 1);
    if(string_mem->string == NULL) {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    memcpy(&(string_mem->string[string_mem->size]), contents, real_size);
    string_mem->size += real_size;
    string_mem->string[string_mem->size] = 0;

    return real_size;
}
