//
// Created by Ming Hu on 8/5/17.
//

#ifndef RMITER_C_MYRMIT_PARSER_H
#define RMITER_C_MYRMIT_PARSER_H

#include "util.h"

// CAS login interface specified details
#define RMIT_SSO_CAS_URL "https://sso-cas.rmit.edu.au/rmitcas/login"
#define RMIT_SSO_CAS_POST_REFFERER RMIT_SSO_CAS_URL

// CAS login interface POST field keys
#define POST_FIELD_USERNAME "username="
#define POST_FIELD_PASSWORD "&password="
#define POST_FIELD_LT_TOKEN "&lt="
#define POST_FIELD_MISC "&execution=e1s1&_eventId=submit&submit=Login"

// myRMIT Portal API URLs
#define RMIT_MYRMIT_ANNOUNCEMENT_URL "https://my.rmit.edu.au/service/announcements"

void myrmit_api_cas_init(char * user_name, char * user_password, char * cookie_path);

const char * get_init_token(char * cookie_file_path);

const char * parse_login_ticket(char * raw_html);

const char * find_attribute(GumboNode * current_node, GumboTag element_tag_type,
                            char * element_term_key, char * element_term_value, char * desired_result_key);

char * myrmit_api_get_myrmit_announcements(char * cookie_path);

#endif //RMITER_C_MYRMIT_PARSER_H
