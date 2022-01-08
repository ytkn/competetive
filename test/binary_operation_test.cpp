#include "binary_operation.hpp"
#include <vector>

#include "gtest/gtest.h"

vector<int> to_vec(int x){
    vector<int> ans;
    while(x){
        ans.push_back(x%2);
        x /= 2;
    }
    return ans;
}

string to_str(int x){
    auto u = to_vec(x);
    reverse(u.begin(), u.end());
    string ans;
    for(int x: u) ans += '0'+x;
    return ans;
}

TEST(binary_operation, add_one) {
    for(int x = 0; x <= 10000; x++){
        ASSERT_EQ(add_one(to_vec(x)), to_vec(x+1));
        ASSERT_EQ(add_one(to_str(x)), to_str(x+1));
    }
    ASSERT_EQ(add_one("1110"), "1111");
    ASSERT_EQ(add_one(vector<int>({0, 1, 1, 1})), vector<int>({1, 1, 1, 1}));
    ASSERT_EQ(add_one("1101"), "1110");
    ASSERT_EQ(add_one(vector<int>({1, 0, 1, 1})), vector<int>({0, 1, 1, 1}));
}
