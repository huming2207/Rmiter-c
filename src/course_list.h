//
// Created by Ming Hu on 8/5/17.
//

#ifndef RMITER_C_COURSE_LIST_H
#define RMITER_C_COURSE_LIST_H

#include "course.h"

typedef struct course_node
{
    Course * course;
    int id;
    struct course_node * previous_node;
    struct course_node * next_node;
    struct course_node * current_node;
} CourseNode;

typedef struct course_list
{
    CourseNode * first_course;
    CourseNode * last_course;
    CourseNode * current_course;
    struct tm * week_start_time;
    int length;
} CourseList;

CourseList * create_course_list();

CourseNode * create_course_node(int id, Course * course);

CourseNode * add_course_to_node(Course * course, CourseNode * node);

CourseNode * remove_course_from_node(Course * course, CourseNode * node);

void delete_course_list(CourseList * list);

void delete_course_node(CourseNode * node);

bool insert_node(CourseList * list, CourseNode * node);

bool remove_current_node(CourseList * list);

CourseNode * find_by_node_id(CourseList * list, int node_id);

#endif //RMITER_C_COURSE_LIST_H
