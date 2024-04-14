cmake_minimum_required(VERSION 3.27)
project(test)
set(CMAKE_CXX_STANDARD 20)

find_package(Python 3.11 COMPONENTS Development REQUIRED)
include_directories(${Python_INCLUDE_DIRS})

add_library(model model.cpp model.h)
target_link_libraries(model ${Python_LIBRARIES} DataBaseLib)