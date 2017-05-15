#include "main.h"

int main()
{
    const char * lt_token = get_init_token("cookie.txt");
    printf("%s", lt_token);
    return 0;
}