//
// Created by Ming Hu on 8/5/17.
//

#include "myrmit_parser.h"

CourseList * myrmit_parse_course(char * raw_json)
{
    // Convert raw json to root object
    cJSON * root_object = cJSON_Parse(raw_json);

    // Parse week starting timestamp and student ID
    cJSON * current_root_children = root_object->child;
    struct tm * time_info = gmtime((time_t*)json_to_long(current_root_children, "weekStartDate"));
    char * student_id = json_to_string(current_root_children, "userId");

    // Convert "weekly_timetable" to object (JSON Object array);
    cJSON * weekly_array = cJSON_GetObjectItemCaseSensitive(root_object, "weeklyTimetable");

    // Parse "weekly_timetable" array with course list initialized
    CourseList * new_course_list = create_course_list();
    int course_node_id = 0;

    for(int weekly_array_index = 0; weekly_array_index < cJSON_GetArraySize(weekly_array); weekly_array_index++)
    {
        // Iterate the object
        cJSON * current_object = cJSON_GetArrayItem(weekly_array, weekly_array_index);

        // Type #1 - Date string
        if(strcmp(current_object->string, "dayDisplayable") == 0)
        {

        }

       // Type #2 - Daily courses
        else if(strcmp(current_object->string, "dailyTimetable") == 0)
        {
           for(int daily_array_index = 0; daily_array_index < cJSON_GetArraySize(current_object); daily_array_index++)
           {
               cJSON * current_course_object = cJSON_GetArrayItem(current_object, daily_array_index);

               char * activity_type; char * catalog_number; char * end_displayable_time;
               char * start_displayable_time; char * title_string; char * subject_string; char * classroom_string;

               if(strcmp(current_course_object->string, "activityType") == 0)
               {
                   activity_type = current_course_object->valuestring;
               }
               else if(strcmp(current_course_object->string, "catalogNumber") == 0)
               {
                    catalog_number = current_course_object->valuestring;
               }
               else if(strcmp(current_course_object->string, "endDisplayable") == 0)
               {
                    end_displayable_time = current_course_object->valuestring;
               }
               else if(strcmp(current_course_object->string, "startDisplayable") == 0)
               {
                    start_displayable_time = current_course_object->valuestring;
               }
               else if(strcmp(current_course_object->string, "title") == 0)
               {
                    title_string = current_course_object->valuestring;
               }
               else if(strcmp(current_course_object->string, "subject") == 0)
               {
                    subject_string = current_course_object->valuestring;
               }
               else if(strcmp(current_course_object->string, "classroom") == 0)
               {
                   classroom_string = current_course_object->valuestring;
               }
           }
        }
    }
}

