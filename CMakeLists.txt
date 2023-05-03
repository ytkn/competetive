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

set(
    tests
    bostan_mori
    and_convolution
    discrete_log
    fft
    int
    mod_int
    mod
    offset_vec
    z_algorithm
    compress
    convex_hull_trick
    ford_fulkerson
    dinic
    euler_tour
    utils
    cumsum_grid
    binary_operation
    aho_corasick
    binary_trie
    mat_sized
    matrix
    max_rectangle_in_histgram
    mo
    rollback_unionfind
    manacher
    longest_common_sequence
    zeta_mobius
)

enable_testing()

foreach(x ${tests})
    add_unit_test(${x})
endforeach()
