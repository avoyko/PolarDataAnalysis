find_package(cpr)
find_package(oatpp)
add_executable(build main.cpp)

target_link_libraries(build cpr)
target_link_libraries(build oatpp)
