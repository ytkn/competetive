#include "and_convolution.hpp"
#include "generator_utils.cpp"

#include "gtest/gtest.h"

vector<long long> naive_and_convolution(vector<long long> u, vector<long long> v, int n){
    vector<long long> ans(1<<n);
    for(int s = 0; s < (1<<n); s++){
        for(int t = 0; t < (1<<n); t++){
            ans[s&t] += u[s]*v[t];
        }
    }
    return ans;
}

void test_and_convolution(vector<long long> u, vector<long long> v, int n){
    auto a0 = and_convolution(u, v, n);
    auto a1 = naive_and_convolution(u, v, n);
    ASSERT_EQ(a0, a1);
}


TEST(and_convolution, and_convolution) {
    int n_exec = 10;
    int n = 10;
    while(n_exec--){
        vector<long long> u(1<<n);
        vector<long long> v(1<<n);
        for(int i = 0; i < (1<<n); i++) u[i] = randint(0, 100000);
        for(int i = 0; i < (1<<n); i++) v[i] = randint(0, 100000);
        test_and_convolution(u, v, n);
    }
}
