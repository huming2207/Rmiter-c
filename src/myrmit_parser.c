//
// Created by Ming Hu on 8/5/17.
//

#include <gumbo.h>
#include "myrmit_parser.h"

void run_cas_init(char * user_name, char * user_password, char * cookie_path)
{



}

const char * get_init_token(char * cookie_file_path)
{
    // Curl declaration
    CURL * curl;
    CURLcode response;

    // Curl init
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    // Detect if it successfully initialized
    if(curl == NULL)
    {
        printf("[ERROR] libCurl init failed!\n");
        exit(1);
    }

    // Curl response string declaration
    CurlString * curlString;
    curlString = malloc(3072);

#ifdef RMITER_DEBUG_CURL

    // Set debug mode
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

#endif

    // Set Curl parameters
    // Set SSO CAS login server URL
    curl_easy_setopt(curl, CURLOPT_URL, RMIT_SSO_CAS_URL);

    // Set write function pointer (see libcurl's example)
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save_response_to_string);

    // Set string struct to write
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)curlString);

    // Set User Agent
    curl_easy_setopt(curl, CURLOPT_USERAGENT, FULL_USER_AGENT);

    // Set cookie file output
    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, cookie_file_path);

    // "Fire in the hole"!!!
    response = curl_easy_perform(curl);

    // See how's everything going...
    if(response != CURLE_OK)
    {
        curl_easy_cleanup(curl);
        return NULL;
    }
    else
    {
        curl_easy_cleanup(curl);
        return parse_login_ticket(curlString->string);
    }

}


const char * parse_login_ticket(char * raw_html)
{
    // Parse HTML into Gumbo memory structure
    GumboOutput * gumbo_output = gumbo_parse(raw_html);

    // Prepare the node
    GumboNode * current_node = gumbo_output->root;

    // Find out the login token...
    // Since the value inside gumbo memory structure will be freed later, we need to duplicate the login ticket.
    const char * gumbo_login_ticket = find_login_ticket(current_node);
    char * login_ticket = malloc(sizeof(char) * strlen(gumbo_login_ticket));
    strcpy(login_ticket, gumbo_login_ticket);

    // Free up memory
    gumbo_destroy_output(&kGumboDefaultOptions, gumbo_output);
    return login_ticket;
}

const char * find_login_ticket(GumboNode * current_node)
{
    const char * lt_token = NULL;

    if (current_node->type != GUMBO_NODE_ELEMENT)
    {
        return NULL;
    }

    GumboAttribute* lt_attr = gumbo_get_attribute(&current_node->v.element.attributes, "name");

    if (lt_attr != NULL && current_node->v.element.tag == GUMBO_TAG_INPUT && (strcmp(lt_attr->value, "lt") == 0))
    {
        lt_token = gumbo_get_attribute(&current_node->v.element.attributes, "value")->value;
        return lt_token;
    }

    GumboVector* children = &current_node->v.element.children;

    for (unsigned int i = 0; i < children->length; ++i)
    {
        lt_token = find_login_ticket(children->data[i]);

        if(lt_token != NULL)
        {
            return lt_token;
        }
    }
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
