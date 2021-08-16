#include "mod_int.hpp"

#include "gtest/gtest.h"

TEST(ModInt, add) {
    ModInt n = 10;
    ModInt m = 20;
    ModInt l = -19;
    ASSERT_EQ(12, (n+2).v);
    ASSERT_EQ(30, (n+m).v);
    ASSERT_EQ(1, (l+m).v);
    ASSERT_EQ(81, (l+100).v);
}


TEST(ModInt, sub) {
    ModInt n = 10;
    ModInt m = 20;
    ModInt l = -19;
    ASSERT_EQ(8, (n-2).v);
    ASSERT_EQ(10, (m-n).v);
    ASSERT_EQ(39, (m-l).v);
}

TEST(ModInt, prod) {
    ModInt n = 10;
    ModInt m = 20;
    ASSERT_EQ(20, (n*2).v);
    ASSERT_EQ(MOD-20, (n*(-2)).v);
    ASSERT_EQ(200, (m*n).v);
}


TEST(ModInt, div) {
    ModInt n = 10;
    ModInt m = 20;
    ASSERT_EQ(5, (n/2).v);
    ASSERT_EQ(2, (m/n).v);
}
