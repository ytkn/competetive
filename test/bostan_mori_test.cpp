#include "bostan_mori.hpp"
#include "generator_utils.cpp"

#include "gtest/gtest.h"

using namespace std;

void test_bostan_mori998244353(vector<mint> c, vector<mint> s, int k){
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

template<typename T>
vector<T> naive_convolution(const vector<T> &u, const vector<T> &v){
    int n = u.size(), m = v.size();
    vector<T> ans(n+m-1);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            ans[i+j] += u[i]*v[j];
        }
    }
    return ans;
}


void test_bostan_mori1000000007(vector<atcoder::modint1000000007> c, vector<atcoder::modint1000000007> s, int k){
    int d = c.size();
    vector<atcoder::modint1000000007> ss(k+1);
    for(int i = 0; i < d; i++) ss[i] = s[i];
    for(int i = d; i <= k; i++){
        for(int j = 0; j < d; j++){
            ss[i] += c[j]*ss[i-j-1];
        }
    }
    for(int i = 0; i <= k; i++) {
        auto x = kth_element<atcoder::modint1000000007, naive_convolution>(c, s, i);
        ASSERT_EQ(ss[i], x);
    }
}


TEST(bostan_mori, test_bostan_mori998244353) {
    int n_iter = 10;
    int n = 50;
    vector<mint> c(n), s(n);
    for(int i = 0; i < n; i++){
        c[i] = randint(1, 100);
        s[i] = randint(1, 100);
    }
    test_bostan_mori998244353(c, s, 1000);
}

TEST(bostan_mori, test_bostan_mori1000000007) {
    int n_iter = 10;
    int n = 50;
    vector<atcoder::modint1000000007> c(n), s(n);
    for(int i = 0; i < n; i++){
        c[i] = randint(1, 100);
        s[i] = randint(1, 100);
    }
    test_bostan_mori1000000007(c, s, 1000);
}