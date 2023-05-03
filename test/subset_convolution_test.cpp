#include "subset_convolution.hpp"
#include "generator_utils.cpp"

#include "gtest/gtest.h"

vector<mint> naive_subset_convolution(vector<mint> a, vector<mint> b, int n){
    vector<mint> ans(1<<n);
    for(int s = 0; s < (1<<n); s++){
        for(int t = s; ; t = (t-1)&s){
            ans[s] += a[t]*b[s-t];
            if(t == 0) break;
        }
    }
    return ans;
}

void test(vector<mint> a, vector<mint> b, int n){
    auto c0 = subset_convolution(a, b, n);
    auto c1 = naive_subset_convolution(a, b, n);
    ASSERT_EQ(c0, c1);
}

TEST(subset_convolution, subset_convolution) {
    int n_exec = 10;
    int n = 10;
    while(n_exec--){
        vector<mint> u(1<<n);
        vector<mint> v(1<<n);
        for(int i = 0; i < (1<<n); i++) u[i] = randint(0, 100000);
        for(int i = 0; i < (1<<n); i++) v[i] = randint(0, 100000);
        test(u, v, n);
    }
}
