cmake_minimum_required(VERSION 3.23)
project(angler)

set(CMAKE_CXX_STANDARD 17)

add_executable(angler angler/main.cpp)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(angler ${SDL2_LIBRARIES})