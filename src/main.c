#include "main.h"

int main()
{
    const char * login_ticket = get_init_token("cookie.txt");
    printf("%s", login_ticket);
    return 0;
}