cmake_minimum_required(VERSION 3.5)

project(csv_task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    csv_task main.cpp
    csvtable.h
    csvtable.cpp
    )
