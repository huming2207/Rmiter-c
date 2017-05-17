//
// Created by Ming Hu on 17/5/17.
//

#include "user_cli.h"


bool require_user_login(char * cookie_path)
{
    printf("[WARN] Invalid cookies found in the path. Please login.\n");
    printf("[WARN] PS: DO NOT RUN this program on CLion if you are not sure about your privacy.\n");
    printf("[WARN]     You password entry WILL BE ECHOED WHEN YOU INPUT!!!\n\n");
    printf("[INFO] Username: ");
    char * user_id = get_user_input(10);
    char * user_password = getpass("[INFO] Password: ");

    return myrmit_api_cas_init(user_id, user_password, cookie_path);
}
