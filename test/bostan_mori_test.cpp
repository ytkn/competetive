#include "bostan_mori.hpp"
#include "generator_utils.cpp"

#include "gtest/gtest.h"

using namespace std;

void test_bostan_mori(vector<mint> c, vector<mint> s, int k){
    int d = c.size();
    vector<mint> ss(k+1);
    for(int i = 0; i < d; i++) ss[i] = s[i];
    for(int i = d; i <= k; i++){
        for(int j = 0; j < d; j++){
            ss[i] += c[j]*ss[i-j-1];
        }
    }
    for(int i = 0; i <= k; i++) ASSERT_EQ(ss[i].val(), kth_element(c, s, i).val());
}

TEST(bostan_mori, bostan_mori) {
    int n_iter = 10;
    int n = 50;
    vector<mint> c(n), s(n);
    for(int i = 0; i < n; i++){
        c[i] = randint(1, 100);
        s[i] = randint(1, 100);
    }
    test_bostan_mori(c, s, 1000);
}