cmake_minimum_required(VERSION 3.27)
project(polar_api)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(gtest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG v1.14.0)
FetchContent_GetProperties(gtest)
if (NOT gtest_POPULATED)
    message(STATUS "Fetching gtest...")
    FetchContent_Populate(gtest)
    add_subdirectory(${gtest_SOURCE_DIR} ${gtest_BINARY_DIR})
endif ()

FetchContent_Declare(cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG master)
FetchContent_GetProperties(cpr)
if (NOT cpr_POPULATED)
    message(STATUS "Fetching cpr...")
    FetchContent_Populate(cpr)
    add_subdirectory(${cpr_SOURCE_DIR} ${cpr_BINARY_DIR})
endif ()

FetchContent_Declare(crow
        GIT_REPOSITORY https://github.com/CrowCpp/Crow
        GIT_TAG master)
FetchContent_GetProperties(crow)
if (NOT crow_POPULATED)
    message(STATUS "Fetching crow...")
    FetchContent_Populate(crow)
    add_subdirectory(${crow_SOURCE_DIR} ${crow_BINARY_DIR})
endif ()


include(sources.cmake)
target_include_directories(polarapi_sources_files PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(polarapi_sources_files cpr::cpr gtest)
add_executable(POLAR_API_TEST test.cpp)
target_link_libraries(POLAR_API_TEST polarapi_sources_files)
set_target_properties(POLAR_API_TEST PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${cmake-build-debug/CMAKE_CURRENT_SOURCE_DIR}")