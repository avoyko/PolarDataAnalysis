find_package(cpr)
add_executable(app wt_module/authorization.cpp)
target_link_libraries(app cpr)

