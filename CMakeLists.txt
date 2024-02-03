cmake_minimum_required(VERSION 3.25)
project(coursework)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory(src)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# include_directories(./json)
# add_subdirectory(json)
include_directories(./cpr)
add_subdirectory(cpr)

find_package(oatpp          1.3.0 REQUIRED)


