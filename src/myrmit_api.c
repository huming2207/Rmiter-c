//
// Created by Ming Hu on 8/5/17.
//

#include <gumbo.h>
#include "myrmit_api.h"

char * myrmit_api_get_data(char * cookie_path, char * desired_url)
{
    // Curl declaration
    CURL * curl = get_rmiter_curl(desired_url);
    CURLcode response;

    // Curl response string declaration
    CurlString * curlString;
    curlString = malloc(CURL_STRING_INIT_SIZE);

    // Load cookies
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, cookie_path);

    // Set cookie file output
    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, cookie_path);

    // Set string struct to write
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)curlString);

    // Turn on auto redirection support
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Set a longer timeout
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);

    // "Fire in the hole"!!!
    response = curl_easy_perform(curl);

    // See how's everything going...
    if(response != CURLE_OK)
    {
        printf("[ERROR] Oops, curl returns an error! Check your network!\n");
        curl_easy_cleanup(curl);
        return NULL;
    }
    else
    {
        // Duplicate string since the original string pointer may be freed by curl_easy_cleanup()
        char * response_str = calloc(strlen(curlString->string), sizeof(char));

        // Do the duplication
        strcpy(response_str, curlString->string);

        // Clean up and return
        curl_easy_cleanup(curl);
        return response_str;
    }
}

bool myrmit_api_cas_init(char * user_name, char * user_password, char * cookie_path)
{
    // Set the initial size of the POST string
    const char * lt_token = get_init_token(cookie_path);
    char * post_field = calloc(1,
                               strlen(POST_FIELD_USERNAME) + strlen(user_name) +
                               strlen(POST_FIELD_PASSWORD) + strlen(user_password) +
                               strlen(POST_FIELD_LT_TOKEN) + strlen(lt_token) +
                               strlen(POST_FIELD_MISC));

    // Merge these strings together...
    strcat(post_field, POST_FIELD_USERNAME);
    strcat(post_field, user_name);
    strcat(post_field, POST_FIELD_PASSWORD);
    strcat(post_field, user_password);
    strcat(post_field, POST_FIELD_LT_TOKEN);
    strcat(post_field, lt_token);
    strcat(post_field, POST_FIELD_MISC);

#ifdef RMITER_DEBUG_CURL

    // POST field debug message
    printf("[DEBUG] POST field is \"%s\", length %d.", post_field, (int)strlen(post_field));

#endif

    // Curl declaration
    CURL * curl = get_rmiter_curl(RMIT_SSO_CAS_URL);
    CURLcode response;

    // Curl response string declaration
    CurlString * curlString;
    curlString = calloc(1, 8192);

    // Set Curl POST request
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_field);

    // Set Curl referrer
    curl_easy_setopt(curl, CURLOPT_REFERER, RMIT_SSO_CAS_POST_REFFERER);

    // Load cookies
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, cookie_path);

    // Set cookie file output
    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, cookie_path);

    // Set string struct to write
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)curlString);

    // "Fire in the hole"!!!
    response = curl_easy_perform(curl);

    // See how's everything going...
    if(response != CURLE_OK)
    {
        printf("[ERROR] Oops, curl returns an error! Check your network!\n");
        curl_easy_cleanup(curl);
    }
    else
    {

#ifdef RMITER_DEBUG_CURL
        printf("%s", curlString->string);
#endif

        curl_easy_cleanup(curl);

        if(strstr(curlString->string, "Successful"))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}

const char * get_init_token(char * cookie_file_path)
{
    // Curl declaration
    CURL * curl = get_rmiter_curl(RMIT_SSO_CAS_URL);
    CURLcode response;

    // Curl response string declaration
    CurlString * curlString;
    curlString = malloc(3072);

    // Set cookie file output
    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, cookie_file_path);

    // Set string struct to write
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)curlString);

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
    const char * gumbo_login_ticket = find_attribute(current_node, GUMBO_TAG_INPUT, "name", "lt", "value");
    char * login_ticket = malloc(sizeof(char) * strlen(gumbo_login_ticket));
    strcpy(login_ticket, gumbo_login_ticket);

    // Free up memory
    gumbo_destroy_output(&kGumboDefaultOptions, gumbo_output);
    return login_ticket;
}

const char * find_attribute(GumboNode * current_node, GumboTag element_tag_type,
                            char * element_term_key, char * element_term_value, char * desired_result_key)
{
    const char * lt_token = NULL;

    // Return NULL if it is in WHITESPACE
    if (current_node->type != GUMBO_NODE_ELEMENT)
    {
        return NULL;
    }

    // Set the element's term key,
    // e.g. if we need to find something like <input name="foobar"> then element search term key is "name",
    //      and element search value is "foobar"
    GumboAttribute* lt_attr = gumbo_get_attribute(&current_node->v.element.attributes, element_term_key);

    if (lt_attr != NULL && current_node->v.element.tag == element_tag_type && (strcmp(lt_attr->value, element_term_value) == 0))
    {
        lt_token = gumbo_get_attribute(&current_node->v.element.attributes, desired_result_key)->value;
        return lt_token;
    }

    GumboVector* children = &current_node->v.element.children;

    for (unsigned int i = 0; i < children->length; ++i)
    {
        lt_token = find_attribute(children->data[i], element_tag_type,
                                  element_term_key, element_term_value, desired_result_key);

        // Force stop and return if it gets a non-null result.
        if(lt_token != NULL)
        {
            return lt_token;
        }
    }

    return lt_token;
}


