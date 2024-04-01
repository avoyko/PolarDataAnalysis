cmake_minimum_required(VERSION 3.27)
project(test)
set(CMAKE_CXX_STANDARD 20)

find_package(Python 3.11 COMPONENTS Development REQUIRED)
include_directories(${Python_INCLUDE_DIRS})

add_executable(CALENDAR_TEST scheduler.cpp)
target_link_libraries(CALENDAR_TEST ${Python_LIBRARIES})
set_target_properties(CALENDAR_TEST PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")