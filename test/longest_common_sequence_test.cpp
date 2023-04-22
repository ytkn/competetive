#include "generator_utils.cpp"
#include "longest_common_sequence.hpp"
#include "gtest/gtest.h"

int naive_lcs(vector<int> s, vector<int> t){
    int n = s.size();
    int m = t.size();
    set<vector<int>> st;
    for(int mask = 0; mask < (1<<n); mask++){
        vector<int> v;
        for(int i = 0; i < n; i++){
            if(mask&(1<<i)) v.push_back(s[i]);
        }
        st.insert(v);
    }
    int ans = 0;
    for(int mask = 0; mask < (1<<m); mask++){
        vector<int> v;
        for(int i = 0; i < m; i++){
            if(mask&(1<<i)) v.push_back(t[i]);
        }
        if(st.count(v)){
            chmax(ans, (int)v.size());
        }
    }
    return ans;
}

void run(int n_kind, int len0, int len1){
    vector<int> s(len0);
    vector<int> t(len1);
    for(int i = 0; i < len0; i++) s[i] = randint(0, n_kind);
    for(int i = 0; i < len1; i++) t[i] = randint(0, n_kind);
    ASSERT_EQ(longest_common_sequence(s, t), naive_lcs(s, t));
}

TEST(longest_common_sequence, lcs) {
    int n_exec = 10;
    // run(1, 0, 0);
    run(1, 10, 10);
    while(n_exec--) {
        run(2, 10, 10);
        run(3, 10, 10);
        run(10, 10, 10);
    }
}
