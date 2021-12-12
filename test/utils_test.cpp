#include "utils.hpp"
#include "generator_utils.cpp"
#include "mod_int.hpp"

#include "gtest/gtest.h"

TEST(utils, ceil_div) {
    int n_test = 100;
    for(int i = 0; i < n_test; i++){
        int a = randint(0, 100000);
        int b = randint(1, 1000);
        int x = ceil_div(a, b);
        ASSERT_TRUE(x*b >= a);
        ASSERT_TRUE((x-1)*b < a);
    }
}

TEST(utils, naive_divide) {
    int n_test = 100;
    int n = 100, m = 20;
    for(int i = 0; i < n_test; i++){
        vector<ModInt> f(n), g(m);
        f[n-1] = 1;
        g[m-1] = 1;
        for(int i = 0; i < n-1; i++) f[i] = randint(0, 100000);
        for(int i = 0; i < m-1; i++) g[i] = randint(0, 100000);
        auto pr = naive_divide(f, g);
        auto p = pr.first;
        auto r = pr.second;
        auto a = naive_convolution(g, p);
        for(int i = 0; i < n; i++){
            if(i < r.size()) ASSERT_EQ(f[i].v, (a[i]+r[i]).v);
            else ASSERT_EQ(f[i].v, a[i].v);
        }
    }
}