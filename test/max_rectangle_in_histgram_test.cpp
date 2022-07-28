#include <algorithm>

#include "max_rectangle_in_histgram.hpp"
#include "generator_utils.cpp"

#include "gtest/gtest.h"

template<typename T>
T naive(vector<T> h){
    int n = h.size();
    auto sub_calc = [&](int l, int r){
        int mn = *min_element(h.begin()+l, h.begin()+r);
        return mn*(r-l);
    };
    T ans = 0;
    for(int l = 0; l < n; l++){
        for(int r = l+1; r <= n; r++){
            ans = max(ans, sub_calc(l, r));
        }
    }
    return ans;
}

TEST(max_rectangle_in_histgram, random_check) {
    auto random_checker = [&](int n){
        vector<int> h(n);
        for(int i = 0; i < n; i++) h[i] = randint(3, 200);
        ASSERT_EQ(max_rectangle_in_histgram(h), naive(h));
    };
    int n_tests = 10;
    while(n_tests--){
        random_checker(10);
        random_checker(100);
    }
}