cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0057 NEW)

project(cmake_example CXX)

find_package(GTest REQUIRED)
include_directories(src)

enable_testing()
GTEST_ADD_TESTS(int_test "" test/int_test.cpp)
GTEST_ADD_TESTS(mod_test "" test/mod_test.cpp)
