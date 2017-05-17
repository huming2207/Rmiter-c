#include "main.h"

int main()
{
    curl_global_init(CURL_GLOBAL_ALL);
    char * json_data = myrmit_api_get_data("cookie.txt", RMIT_MYRMIT_TIMETABLE_URL);
    printf("[TEST] ------ Announcement JSON  ------ \n%s\n ------ Announcement JSON  ------ ",
           json_data);


    CourseList * mylist = myrmit_parse_course(json_data);
    curl_global_cleanup();
    return 0;
}
