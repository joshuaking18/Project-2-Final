cmake_minimum_required(VERSION 3.31)
project(Project_2_Final_main)

set(CMAKE_CXX_STANDARD 14)

include_directories(Project-2-Final-main)

add_executable(Project_2_Final_main
        Project-2-Final-main/functions.cpp
        Project-2-Final-main/functions.h
        Project-2-Final-main/main.cpp)
