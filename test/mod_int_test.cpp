#include "mod_int.hpp"

#include "gtest/gtest.h"
#include "generator_utils.cpp"

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

ModInt naive_power(ModInt x, int r){
    ModInt ans = 1;
    for(int i = 0; i < r; i++) ans *= x;
    return ans;
}

void run_test_pow(int x, int r){
    ModInt expected = naive_power(ModInt(x), r).v;
    ASSERT_EQ(pow(ModInt(x), r).v, expected.v);
    // Fermat's little theorem
    ASSERT_EQ(pow(ModInt(x), r+MOD-1).v, expected.v);
    ASSERT_EQ(pow(ModInt(x), r+(MOD-1)*1000000ll).v, expected.v);
}

TEST(ModInt, power) {
    for(int i = 0; i < 100; i++){
        run_test_pow(randint(1, 10000), randint(1, 1000));
    }
}

ModInt naive_comb(int n, int r){
    ModInt ans = 1;
    for(int i = 0; i < r; i++){
        ans *= n-i;
        ans *= ModInt(i+1).inv();
    }
    return ans;
}

TEST(ModInt, comb){
    init();
    for(int n = 1; n <= 100; n++){
        for(int r = 0; r <= n; r++){
            ASSERT_EQ(comb(n, r).v, naive_comb(n, r).v);
        }
    }
}
