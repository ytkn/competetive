cmake_minimum_required(VERSION 3.0)
project(cmake_example CXX)

find_package(GTest REQUIRED)
include_directories(src)

add_executable(int_test test/int_test.cpp)
target_link_libraries(int_test PRIVATE GTest::GTest GTest::Main )

add_executable(mod_test test/mod_test.cpp)
target_link_libraries(mod_test PRIVATE GTest::GTest GTest::Main )

enable_testing()