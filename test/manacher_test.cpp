#include "generator_utils.cpp"
#include "manacher.hpp"
#include "gtest/gtest.h"

template<typename T>
vector<int> naive_longest_palindrome(vector<T> s){
    int n = s.size();
    int i = 0, j = 0;
    vector<int> r(n);
    for(int i = 0; i < n; i++){
        r[i] = 1;
        for(int j = 1; i-j >= 0 && i+j < n; j++){
            if(s[i-j] == s[i+j]) r[i]++;
            else break;
        }
    }
    return r;
}

void run(int n_kind, int len){
    vector<int> s(len);
    for(int i = 0; i < len; i++) s[i] = randint(0, n_kind);
    ASSERT_EQ(manacher(s), naive_longest_palindrome(s));
}

TEST(manacher, longest_palindrome) {
    int n_exec = 10;
    run(1, 100);
    while(n_exec--) {
        run(2, 100);
        run(3, 100);
        run(10, 100);
    }
}
