//
// Created by Ming Hu on 8/5/17.
//

#include "ical_writer.h"

FILE * ical_init(char * path)
{
    // File IO init
    FILE * file = fopen(path, "w");

    if(file == NULL)
    {
        return NULL;
    }

    // Add header
    fprintf(file, ICAL_HEADER ICAL_NEWLINE);

    // Flush cache and return file
    fflush(file);
    return file;
}

void ical_write_course_list(CourseList * list,  FILE * file)
{
    // Test if file is null
    if(file == NULL)
    {
        printf("[ERROR] File failed to open! Do you have write permission?\n");
    }

    // Print the course list
    CourseNode * course_node = list->first_course;

    while(course_node != NULL)
    {
        // Add a new event
        fprintf(file, ICAL_EVENT_HEADER ICAL_NEWLINE);

        // Create a new UID
        uuid_t new_uid = "";
        char new_uid_str[37];
        uuid_generate_random(new_uid);
        uuid_unparse_lower(new_uid, new_uid_str);

        // Append the new UID
        fprintf(file, ICAL_EVENT_UID_KEY);
        fprintf(file, "%s", new_uid_str);
        fprintf(file, ICAL_EVENT_UID_DOMAIN ICAL_NEWLINE);

        // Get time struct from string
        struct tm * start_time_struct = parse_time_str(course_node->course->date, course_node->course->start_time);
        struct tm * end_time_struct = parse_time_str(course_node->course->date, course_node->course->end_time);

        // Convert time structs back to string
        // The time string formats in ISO8601, e.g. 20170520T193300 <- 19:33:00, 20 May, 2017
        char start_time_str[17];
        char end_time_str[17];
        strftime(start_time_str, 17, "%Y%m%dT%H%M%S", start_time_struct);
        strftime(end_time_str, 17, "%Y%m%dT%H%M%S", end_time_struct);

        // Write time to file
        fprintf(file, ICAL_START_DATE_KEY);
        fprintf(file, start_time_str);
        fprintf(file, ICAL_NEWLINE ICAL_END_DATE_KEY);
        fprintf(file, end_time_str);
        fprintf(file, ICAL_NEWLINE);

        // Write course title and ID to summary
        fprintf(file, ICAL_SUMMARY_KEY);
        fprintf(file, "%s %s", course_node->course->course_id, course_node->course->title);
        fprintf(file, ICAL_NEWLINE);

        // Write details to description
        fprintf(file, ICAL_DESCRIPTION_KEY);
        fprintf(file, "Course name: %s - %s; Course Type: %s; Course classroom: %s; Course date: %s - %s @ %s.",
               course_node->course->course_id, course_node->course->title,
               course_node->course->activity_type,
               course_node->course->classroom,
               course_node->course->start_time, course_node->course->end_time, course_node->course->date);
        fprintf(file, ICAL_NEWLINE);

        // Write classroom to location
        fprintf(file, ICAL_LOCATION_KEY);
        fprintf(file, course_node->course->classroom);
        fprintf(file, ICAL_NEWLINE);

        // Write event footer then flush the cache
        fprintf(file, ICAL_EVENT_FOOTER);
        fprintf(file, ICAL_NEWLINE);
        fflush(file);

        // Loop to next node
        course_node = course_node->next_node;
    }
}

void ical_close(FILE * file)
{
    fprintf(file, ICAL_FOOTER ICAL_NEWLINE);
    fflush(file);
    fclose(file);
}

struct tm * parse_time_str(char * date, char * time)
{
    /*
     * When you query a timetable, myRMIT API returned two strings as well as a UNIX timestamp.
     * You may found out that the UNIX timestamp actually tells you a WRONG time, while the string is correct.
     * As a result, we need to parse the string and convert it back to time struct or time_t.
     *
     * There are two date strings, one is date, another is the time. The format shows in below...
     *
     * - date: Tuesday 16 May 2017
     * - time: 8.30 am
     *
     *
     * Reference: http://www.cplusplus.com/reference/ctime/strftime
     *            http://stackoverflow.com/questions/11213326/how-to-convert-a-string-variable-containing-time-to-time-t-type-in-c
     */

    // Create a new string and combine these two date time string.
    // length -> date's length, space's length (1) and time's length.
    char * date_time_str = calloc(strlen(date) + strlen(time) + 1, sizeof(char));
    strcat(date_time_str, date); strcat(date_time_str, " "); strcat(date_time_str, time);

    // Parse the time to time struct
    struct tm * time_struct = malloc(sizeof(struct tm));
    strptime(date_time_str, "%A %e %B %Y %I.%M %p", time_struct);

    free(date_time_str);
    return time_struct;
}
