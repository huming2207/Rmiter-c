#include "main.h"

int main()
{
    curl_global_init(CURL_GLOBAL_ALL);

    printf("[TEST] ------ Announcement JSON  ------ \n%s\n ------ Announcement JSON  ------ ",
           myrmit_api_get_myrmit_announcements("cookie.txt"));
    curl_global_cleanup();
    return 0;
}