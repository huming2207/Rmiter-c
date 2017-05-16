#include "main.h"

int main()
{
    curl_global_init(CURL_GLOBAL_ALL);

    printf("[TEST] ------ Announcement JSON  ------ \n%s\n ------ Announcement JSON  ------ ",
           myrmit_api_get_data("cookie.txt", RMIT_MYRMIT_ANNOUNCEMENT_URL));
    curl_global_cleanup();
    return 0;
}