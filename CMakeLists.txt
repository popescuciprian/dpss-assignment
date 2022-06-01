cmake_minimum_required(VERSION 3.16)
project(dpss-assignment C)

set(CMAKE_C_STANDARD 99)

add_executable(dpss-assignment main.c)
target_link_libraries(dpss-assignment zip)
