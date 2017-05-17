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
#define POST_FIELD_USERNAME             "username="
#define POST_FIELD_PASSWORD             "&password="
#define POST_FIELD_LT_TOKEN             "&lt="
#define POST_FIELD_MISC                 "&execution=e1s1&_eventId=submit&submit=Login"

// myRMIT Portal API URLs
#define RMIT_MYRMIT_ANNOUNCEMENT_URL    "https://my.rmit.edu.au/service/announcements"
#define RMIT_MYRMIT_TIMETABLE_URL       "https://my.rmit.edu.au/service/myclasstimetable"
#define RMIT_MYRMIT_CURRENT_COURSE_URL  "https://my.rmit.edu.au/service/courseinfo"
#define RMIT_MYRMIT_PAST_COURSE_URL     "https://my.rmit.edu.au/service/courseinfo/past"
#define RMIT_MYRMIT_FUTURE_COURSE_URL   "https://my.rmit.edu.au/service/courseinfo/future"
#define RMIT_MYRMIT_PROGRAMINFO_URL     "https://my.rmit.edu.au/service/programinfo"
#define RMIT_MYRMIT_GRADE_RESULT_URL    "https://my.rmit.edu.au/service/myexamresults/new"
#define RMIT_MYRMIT_PERSONAL_DETAIL_URL "https://my.rmit.edu.au/service/mydetail"

// Initial size of CurlString
#define CURL_STRING_INIT_SIZE           8192

bool myrmit_api_cas_init(char * user_name, char * user_password, char * cookie_path);

const char * get_init_token(char * cookie_file_path);

const char * parse_login_ticket(char * raw_html);

const char * find_attribute(GumboNode * current_node, GumboTag element_tag_type,
                            char * element_term_key, char * element_term_value, char * desired_result_key);

char * myrmit_api_get_data(char * cookie_path, char * desired_url);

#endif //RMITER_C_MYRMIT_PARSER_H
