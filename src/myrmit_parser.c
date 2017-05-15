//
// Created by Ming Hu on 8/5/17.
//

#include "myrmit_parser.h"
#include "../Gumbo/gumbo.h"

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
    curlString = malloc(sizeof(CurlString *));

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
        return parse_login_ticket(curlString->string);
    }

}


const char * parse_login_ticket(char * raw_html)
{
    // Parse HTML into Gumbo memory structure
    GumboOutput * gumbo_output = gumbo_parse(raw_html);

    // Prepare the node
    GumboNode * gumbo_root = gumbo_output->root;

    assert(gumbo_root->type == GUMBO_NODE_ELEMENT);
    assert(gumbo_root->v.element.children.length >= 2);

    const GumboVector* root_children = &gumbo_root->v.element.children;
    
    GumboNode* page_body = NULL;
    
    for (int i = 0; i < root_children->length; ++i)
    {
        GumboNode* child = root_children->data[i];
        if (child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_BODY)
        {
            page_body = child;
            break;
        }
    }

    assert(page_body != NULL);

    GumboVector* page_body_children = &page_body->v.element.children;
    
    for (int i = 0; i < page_body_children->length; ++i)
    {
        GumboNode* child = page_body_children->data[i];

        GumboAttribute * input_name_attr = gumbo_get_attribute(&child->v.element.attributes, "name");

        if (child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_INPUT && strcmp(input_name_attr->value, "lt") == 0)
        {
            GumboAttribute * input_value_attr = gumbo_get_attribute(&child->v.element.attributes, "value");
            return input_name_attr->value;
        }
    }

    return NULL;
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
