cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 20)

find_package(Python 3.11 COMPONENTS Development REQUIRED)
include_directories(${Python_INCLUDE_DIRS})

add_library(SchedulerLib scheduler.cpp)
target_include_directories(SchedulerLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(SchedulerLib ${Python_LIBRARIES})