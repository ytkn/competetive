#include <vector>
#include <cassert>

using namespace std;

template<typename T>
vector<T> supset_zeta(vector<T> v, int n){
    assert(v.size() == (1<<n));
    auto dp = v;
    for(int j = 0; j < n; j++){
        for(int i = 0; i < (1<<n); i++){
            if(!(i&(1 << j))){
                dp[i] += dp[i^(1<<j)];
            }
        }
    }
    return dp;
}

template<typename T>
vector<T> subset_zeta(vector<T> v, int n){
    assert(v.size() == (1<<n));
    auto dp = v;
    for(int j = 0; j < n; j++){
        for(int i = 0; i < (1<<n); i++){
            if(i&(1 << j)){
                dp[i] += dp[i^(1<<j)];
            }
        }
    }
    return dp;
}

template<typename T>
vector<T> supset_mobius(vector<T> v, int n){
    assert(v.size() == (1<<n));
    auto dp = v;
    for(int j = 0; j < n; j++){
        for(int i = 0; i < (1<<n); i++){
            if(!(i & (1 << j))){
                dp[i] -= dp[i^(1<<j)];
            }
        }
    }
    return dp;
}

template<typename T>
vector<T> subset_mobius(vector<T> v, int n){
    assert(v.size() == (1<<n));
    auto dp = v;
    for(int j = 0; j < n; j++){
        for(int i = 0; i < (1<<n); i++){
            if(i&(1 << j)){
                dp[i] -= dp[i^(1<<j)];
            }
        }
    }
    return dp;
}
