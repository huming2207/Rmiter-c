//
// Created by Ming Hu on 8/5/17.
//

#ifndef RMITER_C_COURSE_ARRAY_H
#define RMITER_C_COURSE_ARRAY_H

#include "util.h"


typedef struct course
{
    char * title;
    char * activity_type;
    char * course_id;
    char * start_time;
    char * end_time;
    char * classroom;
} Course;

Course * create_course(char * title, char * activity_type, char * course_id,
                       char * start_time, char * end_time, char * classroom);

void delete_course(Course * course);



#endif //RMITER_C_COURSE_ARRAY_H
