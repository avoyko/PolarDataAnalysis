cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)

file(GLOB POLAR_API_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.cpp)
file(GLOB POLAR_ENDPOINTS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/endpoints/src/*.cpp)

add_library(PolarAPILib ${POLAR_API_SOURCES} ${POLAR_ENDPOINTS_SOURCES})
target_include_directories(PolarAPILib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(PolarAPILib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/endpoints/include)
target_link_libraries(PolarAPILib cpr::cpr)