//
// Created by Ming Hu on 8/5/17.
//

#include "myrmit_parser.h"

CourseList * myrmit_parse_course(char * raw_json)
{
    // Convert raw json to root object
    cJSON * root_object = cJSON_Parse(raw_json);

    // Parse week starting timestamp and student ID, and also weekly timetable
    cJSON * current_root_children = root_object->child;
    char * student_id = NULL;
    cJSON * weekly_array = NULL;
    CourseList * new_course_list = create_course_list();
    int course_node_id = 0;

    while(current_root_children != NULL)
    {
        if(strcmp(current_root_children->string, "userId") == 0)
        {
            student_id = json_to_string(current_root_children, "userId");
        }
        else if(strcmp(current_root_children->string, "weeklyTimetable") == 0 &&
                current_root_children->type == cJSON_Array)
        {
            weekly_array = current_root_children->child;
        }

        current_root_children = current_root_children->next;
    }

    cJSON * current_weekly_object = weekly_array;

    while(current_weekly_object != NULL)
    {
        // Get the current child object for weekly array item
        cJSON * current_weekly_child_object = current_weekly_object->child;

        // Init a date string
        char * date_string = NULL;

        // Type #1 - Date string


            // Type #2 - Daily courses
        if (strcmp(current_weekly_child_object->string, "dailyTimetable") == 0)
        {
            for (int daily_array_index = 0;
                 daily_array_index < cJSON_GetArraySize(current_weekly_child_object);
                 daily_array_index++)
            {
                cJSON * current_course_object = cJSON_GetArrayItem(current_weekly_child_object, daily_array_index)->child;

                char * activity_type = NULL;
                char * catalog_number = NULL;
                char * end_displayable_time = NULL;
                char * start_displayable_time = NULL;
                char * title_string = NULL;
                char * subject_string = NULL;
                char * classroom_string = NULL;

                cJSON * current_course_sub_object = current_course_object;

                // Iterate and parse the specific item string
                while(current_course_sub_object != NULL)
                {
                    if (strcmp(current_course_sub_object->string, "activityType") == 0)
                    {
                        activity_type = duplicate_string(current_course_sub_object->valuestring);
                    }
                    else if (strcmp(current_course_sub_object->string, "catalogNumber") == 0)
                    {
                        catalog_number = duplicate_string(current_course_sub_object->valuestring);
                    }
                    else if (strcmp(current_course_sub_object->string, "endDisplayable") == 0)
                    {
                        end_displayable_time = duplicate_string(current_course_sub_object->valuestring);
                    }
                    else if (strcmp(current_course_sub_object->string, "startDisplayable") == 0)
                    {
                        start_displayable_time = duplicate_string(current_course_sub_object->valuestring);
                    }
                    else if (strcmp(current_course_sub_object->string, "title") == 0)
                    {
                        title_string = duplicate_string(current_course_sub_object->valuestring);
                    }
                    else if (strcmp(current_course_sub_object->string, "subject") == 0)
                    {
                        subject_string = duplicate_string(current_course_sub_object->valuestring);
                    }
                    else if (strcmp(current_course_sub_object->string, "location") == 0)
                    {
                        classroom_string = duplicate_string(current_course_sub_object->valuestring);
                    }

                    current_course_sub_object = current_course_sub_object->next;
                }

                // Here we need to merge catalog number with subject, e.g. COSC9527.
                subject_string = realloc(subject_string, strlen(catalog_number) + strlen(subject_string));
                strcat(subject_string, catalog_number);

                if (strcmp(current_weekly_child_object->next->string, "dayDisplayable") == 0)
                {
                    date_string = duplicate_string(current_weekly_child_object->next->valuestring);
                }

                // Create course
                Course * new_course = create_course(title_string, activity_type,
                                                    subject_string, start_displayable_time,
                                                    end_displayable_time, classroom_string, date_string);
                // Create course node
                CourseNode * new_course_node = create_course_node(course_node_id, new_course);

                // Run insertion to node
                insert_node(new_course_list, new_course_node);

                // Append 1 for course node ID
                course_node_id++;
            }
        }

        // Switch to next item
        current_weekly_object = current_weekly_object->next;
    }

    // Clean up cJSON
    cJSON_free(root_object);

    // Generate list head and tail (i.e. set its first course node pointer and last course pointer)
    set_list_first_last(new_course_list);

    // Return course list
    return new_course_list;
}