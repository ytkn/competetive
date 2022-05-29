#include <vector>
#include <algorithm>

using namespace std;

/**
 * verified(strict=true): https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=6665054
 */ 
template<typename T>
int longest_increasing_sequence(const vector<T> &v, bool strict){
    int n = v.size();
    const T inf = (*max_element(v.begin(), v.end()))+1;
    vector<T> dp(n, inf);
    for(int i = 0; i < n; i++){
        if(strict){
            auto p = lower_bound(dp.begin(), dp.end(), v[i]);
            int j = p-dp.begin();
            dp[j] = v[i];
        }else{
            auto p = upper_bound(dp.begin(), dp.end(), v[i]);
            int j = p-dp.begin();
            dp[j] = v[i];
        }
    }
    for(int j = n-1; j >= 0; j--){
        if(dp[j] != inf) return j+1;
    }
    assert(false);
}