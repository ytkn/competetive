#include "mod_int.hpp"
#include "mat_sized.hpp"

#include "gtest/gtest.h"

using mint = ModInt;

mint fib_kth(ll k){
    Matrix<mint, 2, 2> A(mint(0));
    Matrix<mint, 2, 1> a(mint(0));
    a[0][0] = 0;
    a[1][0] = 1;
    A[0][1] = 1;
    A[1][0] = 1; A[1][1] = 1;
    auto u = (A^k)*a;
    return u[0][0];
}

TEST(mat_sized, fib) {
    vector<mint> fib(10001);
    fib[0] = 0;
    fib[1] = 1;
    for(int i = 2; i <= 10000; i++){
        fib[i] = fib[i-1]+fib[i-2];
    }
    for(int i = 0; i <= 10000; i++){
        ASSERT_EQ(fib_kth(i).v, fib[i].v);
    }
}