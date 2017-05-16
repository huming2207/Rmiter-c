cmake_minimum_required(VERSION 3.7)
project(rmiter_c)
set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-pedantic -Wall -lcurl -lgumbo")
set(SOURCE_FILES src/main.c cJSON/cJSON.c cJSON/cJSON.h src/course.c src/course.h src/json_parser.c src/json_parser.h src/myrmit_api.c src/myrmit_api.h src/ical_writer.c src/ical_writer.h src/main.h src/util.c src/util.h src/course_list.c src/course_list.h)
add_executable(rmiter_c ${SOURCE_FILES})
target_link_libraries(rmiter_c curl gumbo)