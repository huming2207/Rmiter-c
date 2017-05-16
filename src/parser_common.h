//
// Created by Ming Hu on 16/5/17.
//

#ifndef RMITER_C_PARSER_COMMON_H
#define RMITER_C_PARSER_COMMON_H

#include "util.h"

char * json_to_string(cJSON * cjson, char * key);

long json_to_long(cJSON * cjson, char * key);

#endif //RMITER_C_PARSER_COMMON_H
