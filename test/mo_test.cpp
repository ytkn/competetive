#include "mo.hpp"
#include "generator_utils.cpp"

#include "gtest/gtest.h"


TEST(mo, number_of_unique) {
    int n = 1000;
    vector<int> a(n);
    for(int i = 0; i < n; i++) a[i] = randint(0, 100);
    int m = 1000;
    vector<int> l(m), r(m);
    Mo<int> mo(sqrt(n));
    for(int i = 0; i < m; i++){
        l[i] = randint(0, n);
        r[i] = randint(l[i], n+1);
        mo.add_query(l[i], r[i]);
    }
    int ans = 0;
    vector<int> cnt(100);
    auto add = [&](int i){
        if(cnt[a[i]] == 0) ans++; 
        cnt[a[i]]++;
    };
    auto del = [&](int i){
        if(cnt[a[i]] == 1) ans--; 
        cnt[a[i]]--;
    };
    auto get_ans = [&](){
        return ans;
    };
    auto w = mo.solve(add, del, get_ans);
    for(int i = 0; i < m; i++){
        set<int> st;
        for(int j = l[i]; j < r[i]; j++){
            st.insert(a[j]);
        }
        ASSERT_EQ(w[i], (int)st.size());
    }
}