cmake_minimum_required(VERSION 3.23)
project(Task1)

set(CMAKE_CXX_STANDARD 20)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(Task1 villagegame.h main.cpp roundphases.cpp turnphases.cpp setup.cpp cli.cpp main.cpp actions.cpp AI.cpp other.cpp)

target_link_libraries(Task1 ${CURSES_LIBRARIES})
