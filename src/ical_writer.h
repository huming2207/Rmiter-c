//
// Created by Ming Hu on 8/5/17.
//

#ifndef RMITER_C_ICAL_WRITER_H
#define RMITER_C_ICAL_WRITER_H

#include "util.h"
#include "course_list.h"
#include <uuid/uuid.h>

FILE * ical_init(char * path);

void ical_write_course_list(CourseList * list,  FILE * file);

void ical_close(FILE * file);

struct tm * parse_time_str(char * date, char * time);


// RFC5545 iCalendar content macros
// For more details, please refer to Wikipedia, or this: http://www.kanzaki.com/docs/ical/description.html

// New line (CRLF)
#define ICAL_NEWLINE            "\r\n"

// "Header"
#define ICAL_HEADER             "BEGIN:VCALENDAR\r\nVERSION:2.0\r\nPRODID:-//Jackson Hu//RMITer iCalendar Generator 1.0//EN"

// "Footer"
#define ICAL_FOOTER             "END:VCALENDAR"

// Event header
#define ICAL_EVENT_HEADER       "BEGIN:VEVENT"

// Event footer
#define ICAL_EVENT_FOOTER       "END:VEVENT"

// UID
#define ICAL_EVENT_UID_KEY      "UID:"
#define ICAL_EVENT_UID_DOMAIN   "@jacksonhu.com"

// Date Stamp (key)
#define ICAL_DATESTAMP_KEY      "DTSTAMP:"

// Organizer (Fake, of course)
#define ICAL_ORGANIZER          "ORGANIZER;CN=Your Uni:MAILTO:john.doe@example.com"

// Start date (key)
#define ICAL_START_DATE_KEY     "DTSTART;TZID=Australia/Melbourne:"

// End date (key)
#define ICAL_END_DATE_KEY       "DTEND;TZID=Australia/Melbourne:"

// Summary (key)
#define ICAL_SUMMARY_KEY        "SUMMARY:"

// Location (key)
#define ICAL_LOCATION_KEY       "LOCATION:"

// Description (key)
#define ICAL_DESCRIPTION_KEY    "DESCRIPTION:"



#endif //RMITER_C_ICAL_WRITER_H
