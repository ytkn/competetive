#include "z_algorithm.hpp"
#include "print.hpp"
#include <random>

#include "gtest/gtest.h"

/**
 * ランダムに文字列を生成する。
 * n: 使用する文字の種類
 * m: 文字列の長さ
 */
string random_generator(int n, int len){
    string ret;
    for(int i = 0; i < len; i++) {
        int m = rand()%n;
        ret += 'a'+m;
    }
    return ret;
}

vector<int> simple_lcp(string s){
    int n = s.size();
    vector<int> ans(n);
    ans[0] = n;
    for(int i = 1; i < n; i++){
        for(int j = 0; i+j < n; j++){
            ans[i] = j+1;
            if(s[i+j] != s[j]) {
                ans[i] = j;
                break;
            }
        }
    }
    return ans;
}

bool compare_vector(vector<int> v, vector<int> u){
    if(v.size() != u.size()) return false;
    int n = v.size();
    for(int i = 0; i < n; i++) {
        if(v[i] != u[i]) return false;
    }
    return true;
}

TEST(z_algorithm, run) {
    string s = random_generator(2, 10);
    ASSERT_TRUE(compare_vector(z_algorithm(s), simple_lcp(s)));
    s = random_generator(2, 100);
    ASSERT_TRUE(compare_vector(z_algorithm(s), simple_lcp(s)));
    s = random_generator(2, 1000);
    ASSERT_TRUE(compare_vector(z_algorithm(s), simple_lcp(s)));
    s = random_generator(3, 1000);
    ASSERT_TRUE(compare_vector(z_algorithm(s), simple_lcp(s)));
    s = random_generator(20, 100);
    ASSERT_TRUE(compare_vector(z_algorithm(s), simple_lcp(s)));
}


