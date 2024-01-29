find_package(cpr)
add_executable(build main.cpp)

target_link_libraries(build cpr)