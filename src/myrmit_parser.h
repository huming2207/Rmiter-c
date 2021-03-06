//
// Created by Ming Hu on 8/5/17.
//

#ifndef RMITER_C_JSON_PARSER_H
#define RMITER_C_JSON_PARSER_H

#include "util.h"
#include "course_list.h"
#include "course.h"
#include "parser_common.h"
#include "myrmit_api.h"
#include "user_cli.h"

CourseList * myrmit_parse_course(char * raw_json, char * cookie_path);


#endif //RMITER_C_JSON_PARSER_H
