cmake_minimum_required(VERSION 3.16)

project(aoc2024)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include_directories(common)

add_executable(day01a day01/main_a.cpp)
add_executable(day01b day01/main_b.cpp)
add_executable(day02a day02/main_a.cpp)
add_executable(day02b day02/main_b.cpp)
