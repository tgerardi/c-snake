cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)

find_package(raylib REQUIRED)

include_directories(include)

add_executable(SnakeGame src/snake.cpp)

target_link_libraries(SnakeGame raylib)

if(UNIX AND NOT APPLE)
    target_link_libraries(SnakeGame GL m pthread dl rt X11)
endif()

install(TARGETS SnakeGame DESTINATION /usr/local/bin)