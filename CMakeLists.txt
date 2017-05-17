cmake_minimum_required(VERSION 3.7)
project(rmiter_c)
set(CMAKE_C_STANDARD 99)

# Since macOS use clang by default, and it seems does not support "-l" argument.
# So, add a judgement ignore it anyway.
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_C_FLAGS "-pedantic -Wall -Wno-unused-function")
else()
    set(CMAKE_C_FLAGS "-pedantic -Wall -lcurl -lgumbo -Wno-unused-function")
endif()


set(SOURCE_FILES src/main.c cJSON/cJSON.c cJSON/cJSON.h src/course.c src/course.h src/myrmit_parser.c src/myrmit_parser.h src/myrmit_api.c src/myrmit_api.h src/ical_writer.c src/ical_writer.h src/main.h src/util.c src/util.h src/course_list.c src/course_list.h src/parser_common.c src/parser_common.h src/user_cli.c src/user_cli.h)
add_executable(rmiter_c ${SOURCE_FILES})

target_link_libraries(rmiter_c curl gumbo)