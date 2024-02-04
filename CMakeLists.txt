cmake_minimum_required(VERSION 3.25)
project(coursework)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory(src)
add_subdirectory(cpr)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(./cpr)




