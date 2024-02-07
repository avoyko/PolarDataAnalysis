find_package(cpr)

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

include(sources.cmake)
target_include_directories(sources_files PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sources_files cpr yaml-cpp::yaml-cpp)
add_executable(application authorization/authorization.cpp)
target_link_libraries(application sources_files)