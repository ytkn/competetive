cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0057 NEW)

project(cmake_example CXX)

find_package(GTest REQUIRED)
include_directories(src)

add_executable(int_test test/int_test.cpp)
target_link_libraries(int_test PRIVATE GTest::GTest GTest::Main )

add_executable(mod_test test/mod_test.cpp)
target_link_libraries(mod_test PRIVATE GTest::GTest GTest::Main )

add_executable(z_algorithm_test test/z_algorithm_test.cpp)
target_link_libraries(z_algorithm_test PRIVATE GTest::GTest GTest::Main )

add_executable(discrete_log_test test/discrete_log_test.cpp)
target_link_libraries(discrete_log_test PRIVATE GTest::GTest GTest::Main )

enable_testing()
GTEST_ADD_TESTS(int_test "" test/int_test.cpp)
GTEST_ADD_TESTS(mod_test "" test/mod_test.cpp)
GTEST_ADD_TESTS(z_algorithm_test "" test/z_algorithm_test.cpp)
GTEST_ADD_TESTS(discrete_log_test "" test/discrete_log_test.cpp)

