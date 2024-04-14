cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 20)

add_library(SchedulerLib scheduler.cpp)
target_include_directories(SchedulerLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)