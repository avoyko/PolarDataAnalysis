cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)

file(GLOB DATABASE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.cpp)

add_library(:DataBaseLib ${DATABASE_SOURCES})
target_include_directories(DataBaseLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(DataBaseLib PolarAPILib frozen::frozen mysql::concpp)