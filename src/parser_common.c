//
// Created by Ming Hu on 16/5/17.
//

#include "parser_common.h"


char * json_to_string(cJSON * cjson, char * key)
{
    cJSON * current_root_children = cjson->child;
    char * string_result = NULL;

    // Iterate and find the stuff we need.
    while(current_root_children != NULL)
    {
        if(strcmp(current_root_children->string, key) == 0)
        {
            // Get a clean memory
            string_result = calloc(1, sizeof(current_root_children->valuestring));
            strcpy(string_result, current_root_children->valuestring);
            break;
        }
        current_root_children = current_root_children->next;
    }

    return string_result;
}

long json_to_long(cJSON * cjson, char * key)
{
    cJSON * current_root_children = cjson->child;
    long int_result = 0;

    // Iterate and find the stuff we need.
    while(current_root_children != NULL)
    {
        if(strcmp(current_root_children->string, key) == 0)
        {
            int_result = strtol(current_root_children->string, NULL, 10);
            break;
        }
        current_root_children = current_root_children->next;
    }

    // See if it is actually valid
    return int_result;
}
