#include "zeta_mobius.hpp"
#include "generator_utils.cpp"

#include "gtest/gtest.h"

vector<long long> naive_sum_subset(vector<long long> v, int n){
    vector<long long> ans(1<<n);
    for(int s = 0; s < (1<<n); s++){
        for(int t = s; ; t = (t-1)&s){
            ans[s] += v[t];
            if(t == 0) break;
        }
    }
    return ans;
}

vector<long long> naive_sum_supset(vector<long long> v, int n){
    vector<long long> ans(1<<n);
    for(int s = 0; s < (1<<n); s++){
        for(int t = s; ; t = (t-1)&s){
            ans[t] += v[s];
            if(t == 0) break;
        }
    }
    return ans;
}

void test_zeta_mobius_subset(vector<long long> v, int n){
    auto z0 = subset_zeta(v, n);
    auto z1 = naive_sum_subset(v, n);
    ASSERT_EQ(z0, z1);
    auto m = subset_mobius(z0, n);
    ASSERT_EQ(v, m);
}

void test_zeta_mobius_supset(vector<long long> v, int n){
    auto z0 = supset_zeta(v, n);
    auto z1 = naive_sum_supset(v, n);
    ASSERT_EQ(z0, z1);
    auto m = supset_mobius(z0, n);
    ASSERT_EQ(v, m);
}

TEST(zeta_mobius, zeta_mobius) {
    int n_exec = 10;
    // run(1, 0, 0);
    int n = 10;
    while(n_exec--){
        vector<long long> v(1<<n);
        for(int i = 0; i < (1<<n); i++) v[i] = randint(0, 100000);
        test_zeta_mobius_subset(v, n);
        test_zeta_mobius_supset(v, n);
    }
}
