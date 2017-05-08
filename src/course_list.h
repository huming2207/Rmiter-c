//
// Created by Ming Hu on 8/5/17.
//

#ifndef RMITER_C_COURSE_LIST_H
#define RMITER_C_COURSE_LIST_H

#include "course.h"

typedef struct course_node
{
    Course * course;
    struct course_node * previous_node;
    struct course_node * next_node;
    struct course_node * current_node;
} CourseNode;

typedef struct course_list
{
    Course * first_course;
    Course * last_course;
    Course * current_course;
    int length;
} CourseList;

CourseList * create_course_list();

CourseNode * create_course_node();

void delete_course_list(CourseList * list);

void delete_course_node(CourseNode * node);

bool insert_node(CourseList * list, CourseNode * node);

bool remove_node(CourseList * list, CourseNode * node);

CourseNode * find_by_course_id(CourseNode * node, char * course_id);

#endif //RMITER_C_COURSE_LIST_H
