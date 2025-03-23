cmake_minimum_required(VERSION 3.30)
project(Grim C)

set(CMAKE_C_STANDARD 11)

ADD_EXECUTABLE(Grim src/main.c)

target_link_libraries(Grim -lncurses)