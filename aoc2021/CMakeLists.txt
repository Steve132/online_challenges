cmake_minimum_required(VERSION 3.14)

project(aoc2021)




set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(day1a day1a.cpp)
add_executable(day1b day1b.cpp)
add_executable(day2a day2a.cpp)
add_executable(day2b day2b.cpp)
add_executable(day3a day3a.cpp)
add_executable(day3b day3b.cpp)
#target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)
