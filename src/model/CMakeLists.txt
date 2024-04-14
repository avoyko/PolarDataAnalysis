cmake_minimum_required(VERSION 3.27)
project(test)
set(CMAKE_CXX_STANDARD 20)

add_library(model model.cpp)
target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(model DataBaseLib SchedulerLib)