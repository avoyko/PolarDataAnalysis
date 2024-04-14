cmake_minimum_required(VERSION 3.27)

include(FetchContent)
FetchContent_Declare(yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG master)
FetchContent_GetProperties(yaml-cpp)
if (NOT yaml-cpp_POPULATED)
    message(STATUS "Fetching yaml-cpp...")
    FetchContent_Populate(yaml-cpp)
    add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
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

add_subdirectory(polar_api)
add_subdirectory(database)
add_subdirectory(model)
add_subdirectory(calendar_scheduler)

add_executable(application main.cpp app/driver.cpp)
target_link_libraries(application model DataBaseLib SchedulerLib PolarAPILib yaml-cpp::yaml-cpp)