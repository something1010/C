cmake_minimum_required(VERSION 3.23)
project(angler)

set(CMAKE_CXX_STANDARD 14)

add_executable(angler main.cpp)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(angler ${SDL2_LIBRARIES})