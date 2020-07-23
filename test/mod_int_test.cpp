#include "mod_int.hpp"

#include "gtest/gtest.h"

TEST(ModInt, add) {
    ModInt n = 10;
    ModInt m = 20;
    ASSERT_EQ(12, (n+2).v);
    ASSERT_EQ(30, (n+m).v);
}


TEST(ModInt, sub) {
    ModInt n = 10;
    ModInt m = 20;
    ASSERT_EQ(8, (n-2).v);
    ASSERT_EQ(10, (m-n).v);
}

TEST(ModInt, prod) {
    ModInt n = 10;
    ModInt m = 20;
    ASSERT_EQ(20, (n*2).v);
    ASSERT_EQ(200, (m*n).v);
}


TEST(ModInt, div) {
    ModInt n = 10;
    ModInt m = 20;
    ASSERT_EQ(5, (n/2).v);
    ASSERT_EQ(2, (m/n).v);
}
