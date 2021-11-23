cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0057 NEW)

project(cmake_example CXX)

find_package(GTest REQUIRED)
include_directories(src)
include_directories(generator)

function(add_unit_test name)
    add_executable(${name}_test test/${name}_test.cpp)
    target_link_libraries(${name}_test PRIVATE GTest::GTest GTest::Main)
    GTEST_ADD_TESTS(${name}_test "" test/${name}_test.cpp)
endfunction()

set(tests discrete_log fft int mod_int mod offset_vec z_algorithm compress convex_hull_trick ford_fulkerson dinic)

enable_testing()

foreach(x ${tests})
    add_unit_test(${x})
endforeach()
