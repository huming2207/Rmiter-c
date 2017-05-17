//
// Created by Ming Hu on 8/5/17.
//

#include "course.h"

Course * create_course(char * title, char * activity_type, char * course_id,
                       char * start_time, char * end_time, char * classroom, char * date)
{
    // Do nothing but just malloc a pointer for course and set the sub-pointers
    Course * course = malloc(sizeof(Course));

    course->activity_type = activity_type;
    course->classroom = classroom;
    course->course_id = course_id;
    course->end_time = end_time;
    course->start_time = start_time;
    course->title = title;
    course->date = date;

    return course;
}

void delete_course(Course * course)
{
    free(course);
}
