find_package(cpr)
# find_package(json)
add_executable(build main.cpp)

target_link_libraries(build cpr)
# target_link_libraries(build json)