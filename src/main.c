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
    printf("[TEST] ------ Timetable JSON  ------ \n%s\n ------ Timetable JSON  ------\n\n\n",
           json_data);

    // Get the course list (in the current week)
    CourseList * mylist = myrmit_parse_course(json_data, "cookie.txt");

    // Write to file
    FILE * file = ical_init("test.ics");
    ical_write_course_list(mylist, file);
    ical_close(file);

    // Clean up and finish
    curl_global_cleanup();
}
