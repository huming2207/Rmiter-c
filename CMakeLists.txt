cmake_minimum_required(VERSION 3.7)
project(rmiter_c)
set(CMAKE_C_STANDARD 99)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_MACOSX_RPATH 1)
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cJSON)
set(SOURCE_FILES main.c mylist.c mylist.h)
add_executable(rmiter_c ${SOURCE_FILES})