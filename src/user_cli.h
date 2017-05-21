//
// Created by Ming Hu on 17/5/17.
//

#ifndef RMITER_C_USER_CLI_H
#define RMITER_C_USER_CLI_H

#include "util.h"
#include "myrmit_parser.h"

bool require_user_login(char * cookie_path);

void auto_crawl_all_weeks();

#endif //RMITER_C_USER_CLI_H
