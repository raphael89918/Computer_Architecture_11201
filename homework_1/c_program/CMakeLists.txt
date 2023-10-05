cmake_minimum_required(VERSION 3.10)

project(homework_1)

add_executable(main main.c)
# add_executable(test test.c)

add_library(round_function round_function.c)

target_link_libraries(main round_function)

