#include "main.h"

int main()
{
    demo_course();
    return 0;
}


void demo_course()
{
    curl_global_init(CURL_GLOBAL_ALL);

    // If cookie cache file does not exist, ask user login and create one.
    if(!file_exist("cookie.txt"))
    {
        bool login_result = require_user_login("cookie.txt");

        if(login_result)
        {
            printf("[INFO] Login successful. Please re-run this program to fetch data.\n");
        }
        else
        {
            printf("[INFO] Login seems failed. Please try again.\n");
        }

        exit(0);
    }



    // Get timetable API data
    char * json_data = myrmit_api_get_data("cookie.txt", RMIT_MYRMIT_TIMETABLE_URL);

    // +1s to ensure the raw JSON is buffered.
    sleep(1);

    // Print raw JSON for debugging.
    printf("[TEST] ------ Announcement JSON  ------ \n%s\n ------ Announcement JSON  ------\n\n\n",
           json_data);

    // Get the course list (in the current week)
    CourseList * mylist = myrmit_parse_course(json_data, "cookie.txt");

    // Print the course list
    CourseNode * course_node = mylist->last_course;

    while(course_node != NULL)
    {
        printf("[TEST] Course name: %s - %s; Course Type: %s; \n[TEST] Course classroom: %s; Course date: %s - %s @ %s.\n\n",
               course_node->course->course_id, course_node->course->title,
               course_node->course->activity_type,
               course_node->course->classroom,
               course_node->course->start_time, course_node->course->end_time, course_node->course->date);

        course_node = course_node->previous_node;
    }

    // Clean up and finish
    curl_global_cleanup();
}
