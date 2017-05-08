cmake_minimum_required(VERSION 3.7)
project(rmiter_c)
set(CMAKE_C_STANDARD 99)


set(SOURCE_FILES main.c mylist.c mylist.h)
add_executable(rmiter_c ${SOURCE_FILES})