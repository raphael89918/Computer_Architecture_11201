cmake_minimum_required(VERSION 3.10)

project(homework_1)

add_library(round_function round_function.c)
add_library(fp32tobf16 fp32tobf16.c)

add_executable(test test.c)
target_link_libraries(test round_function)

add_executable(main main.c)
target_link_libraries(main round_function)
target_link_libraries(main fp32tobf16)
