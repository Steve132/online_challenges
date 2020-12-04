#Per-target based macro is better in 2020, but this is easier and I'll have LOTS of targets
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(aoc aoc.hpp aoc.cpp)
macro(aoctarget NAME)
add_executable(${NAME} ${NAME}.cpp)
target_link_libraries(${NAME} aoc)
endmacro()

aoctarget(day1a)
aoctarget(day1b)
aoctarget(day2a)
aoctarget(day2b)
aoctarget(day3a)
aoctarget(day3b)
