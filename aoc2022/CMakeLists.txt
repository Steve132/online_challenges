cmake_minimum_required(VERSION 3.16)

project(aoc2022)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(day01 day01/main.cpp)
add_executable(day02 day02/main.cpp)

#add_executable(day1b day1b.cpp)