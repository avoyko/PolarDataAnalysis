include(FetchContent)
FetchContent_Declare(yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG master)
FetchContent_GetProperties(yaml-cpp)
if(NOT yaml-cpp_POPULATED)
    message(STATUS "Fetching yaml-cpp...")
    FetchContent_Populate(yaml-cpp)
    add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
endif()

FetchContent_Declare(cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG master)
FetchContent_GetProperties(cpr)
if(NOT cpr_POPULATED)
    message(STATUS "Fetching cpr...")
    FetchContent_Populate(cpr)
    add_subdirectory(${cpr_SOURCE_DIR} ${cpr_BINARY_DIR})
endif()

find_package(mysql-concpp REQUIRED)
if (mysql-concpp_FOUND)
    message(STATUS "Successfully found mysql...")
    include_directories(${mysql-concpp_DIR}/include)
    link_directories(${mysql-concpp_DIR}/lib)
endif (mysql-concpp_FOUND)

include(sources.cmake)
target_include_directories(sources_files PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sources_files cpr::cpr yaml-cpp::yaml-cpp libmysqlcppconn8.2.8.3.0.dylib)
add_executable(application web/driver.cpp)
target_link_libraries(application sources_files)
