#include "main.h"

int main(int argc, char ** argv)
{
    int opt_index = 0;
    char * day_arg = NULL;
    char * month_arg = NULL;
    char * year_arg = NULL;
    char * file_arg = NULL;

    // Prepare arguments
    struct option arg_options[] = {
            {"help",    no_argument,       NULL, 'h'},
            {"day",     required_argument, NULL, 'd'},
            {"month",   required_argument, NULL, 'm'},
            {"year",    required_argument, NULL, 'y'},
            {"output",  required_argument, NULL, 'o'}
    };

    while((opt_index = getopt_long(argc, argv, "hd:m:y:o:", arg_options, NULL)) != -1)
    {
        switch(opt_index)
        {
            case 'h':
            {
                printf("Yet another myRMIT client, written in pure C99\n"
                       "Convert your myRMIT course timetable to iCalendar!\n"
                       "\n"
                       "Usage:\n"
                       "\n"
                       "-h\tPrint this help information\n"
                       "-d\tSpecify the DAY of Week 1’s Monday (with 2 digit)\n"
                       "-m\tSpecify the MONTH of Week 1’s Monday (with 2 digit, e.g. February->02)\n"
                       "-y\tSpecify the YEAR of Week 1’s Monday (with 2 digit, e.g. 2017->17)\n"
                       "-f\tSpecify the output file base directory\n"
                       "\n"
                       "Made by “Jackson“ Ming Hu @ jacksonhu.com, 2017.\n"
                       "Licensed under CC-BY-NC-SA 3.0 Australian version.\n"
                       "This project and its source code are not affiliated with RMIT University.\n"
                       "This project also contains some reverse engineering works, so it should be used for "
                       "research and education purposes only. Although this project is fully open-source, "
                       "it comes with ABSOLUTELY NO WARRANTY. Use at your own risk anyway.\n");
                exit(0);
            }
            case 'd':
            {
                day_arg = strdup(optarg);
                break;
            }
            case 'm':
            {
                month_arg = strdup(optarg);
                break;
            }
            case 'y':
            {
                year_arg = strdup(optarg);
                break;
            }
            case 'o':
            {
                file_arg = strdup(optarg);
                break;
            }
            default:
            {
                printf("\n[ERROR] Please specify your arguments correctly.\nUsage: ./rmiter_c -dmyfh\n");
                exit(0);
            }
        }
    }

    if(!day_arg || !month_arg || !year_arg || !file_arg)
    {
        printf("\n[ERROR] Please specify your arguments correctly.\nUsage: ./rmiter_c -dmyfh\n");
        exit(0);
    }

    struct tm initial_time;
    initial_time.tm_year = str_to_int(year_arg);
    initial_time.tm_mon = str_to_int(month_arg) - 1;
    initial_time.tm_mday = str_to_int(day_arg);

    crawl_all_courses(&initial_time, file_arg);
    return 0;
}


void crawl_all_courses(struct tm * time, char * file_path)
{
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


    for(int week_index = 0; week_index <= 11; week_index++)
    {
        // Prepare time string, e.g. 27 Feb, 2017 -> 270217
        time->tm_mday = time->tm_mday + (7 * week_index);
        mktime(time);
        char time_str[8];
        strftime(time_str, 8, "%d%m%y", time);

        // Prepare API URL (need to append time string with length +7 and a "\0")
        char * api_url = calloc(strlen(RMIT_MYRMIT_TIMETABLE_URL) + 8, sizeof(char));
        strcat(api_url, RMIT_MYRMIT_TIMETABLE_URL);
        strcat(api_url, "/");
        strcat(api_url, time_str);

        // Get timetable API data
        char * json_data = myrmit_api_get_data("cookie.txt", api_url);

        // +2s to ensure the raw JSON is buffered.
        sleep(2);

#ifdef RMITER_DEBUG_CURL
        // Print raw JSON for debugging.
        printf("[TEST] ------ Timetable JSON  ------ \n%s\n ------ Timetable JSON  ------\n\n\n",
               json_data);
#endif

        // Get the course list (in the current week)
        CourseList * mylist = myrmit_parse_course(json_data, "cookie.txt");

        // Generate ics file name
        char ics_file_name[PATH_MAX];
        sprintf(ics_file_name, "%s/Week%d.ics", file_path, week_index);

        // Write to file
        FILE * file = ical_init(ics_file_name);
        ical_write_course_list(mylist, file);
        ical_close(file);
    }

    // Clean up and finish
    if(remove("cookie.txt") != 0)
    {
        printf("[WARN] Cookie cache cannot be removed. Please remove it manually to protect your privacy.\n");
    }
}
