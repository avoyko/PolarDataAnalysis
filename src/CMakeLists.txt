find_package(cpr)
find_package(oatpp)
add_executable(build main.cpp
        utilities.hpp
        oauth2.hpp
        oauth2.cpp
        accesslink.hpp
        accesslink.cpp
        wt_module/authorization.cpp)

target_link_libraries(build cpr)
target_link_libraries(build oatpp)
