cmake_minimum_required(VERSION 3.27)
project(db)
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


find_package(mysql-concpp REQUIRED)
if (mysql-concpp_FOUND)
    message(STATUS "Successfully found mysql...")
    include_directories(${mysql-concpp_DIR}/include)
    link_directories(${mysql-concpp_DIR}/lib)
endif (mysql-concpp_FOUND)


FetchContent_Declare(frozen
        GIT_REPOSITORY https://github.com/serge-sans-paille/frozen
        GIT_TAG master)
FetchContent_GetProperties(frozen)
if (NOT frozen_POPULATED)
    message(STATUS "Fetching frozen...")
    FetchContent_Populate(frozen)
    add_subdirectory(${frozen_SOURCE_DIR} ${frozen_BINARY_DIR})
endif ()

include(sources.cmake)
target_include_directories(db_sources_files PUBLIC ..)
target_link_libraries(db_sources_files frozen cpr::cpr mysql::concpp gtest)
add_executable(DATABASE_TEST test.cpp)
target_link_libraries(DATABASE_TEST db_sources_files)
set_target_properties(DATABASE_TEST PROPERTIES RUNTIME_OUTPUT_DIRECTORY "..")