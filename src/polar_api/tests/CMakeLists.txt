add_executable(POLAR_API_TEST test.cpp)
target_link_libraries(POLAR_API_TEST PolarAPILib gtest yaml-cpp)