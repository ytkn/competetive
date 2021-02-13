#include <vector>
#include "mod_int.hpp"

using namespace std;

/**
 * aで表される多項式にxを代入したときの値を返します。
 */ 
ModInt calc(vector<ModInt> a, ModInt x){
    ModInt cur = 1;
    ModInt ans = 0;
    for(auto b : a){
        ans += b*cur;
        cur *= x;
    }
    return ans;
}

/**
 * f(x_i) = y_iを満たす多項式を返します(O(N^2))
 * verified: https://atcoder.jp/contests/abc137/submissions/20140907
 */ 
vector<ModInt> lagrange_interpolation(vector<ModInt> x, vector<ModInt> y){
    assert(x.size() == y.size());
    int n = x.size();
    vector<vector<ModInt>> dp(2, vector<ModInt>(n+1));
    dp[0][0] = x[0]*(-1);
    dp[0][1] = 1;
    for(int i = 1; i < n; i++){
        int cur = i%2, prev = (i+1)%2;
        dp[cur][0] = dp[prev][0]*x[i]*(-1);
        for(int j = 1; j <= i+1; j++){
            dp[cur][j] = dp[prev][j-1]-dp[prev][j]*x[i];
        }
    }
    vector<ModInt> f(n+1);
    for(int i = 0; i <= n; i++) f[i] = dp[(n-1)%2][i];
    vector<ModInt> ans(n);
    for(int i = 0; i < n; i++){
        ModInt prod = 1;
        for(int j = 0; j < n; j++){
            if(i != j) prod *= (x[i]-x[j]);
        }
        // (x-x[i])*q = f
        vector<ModInt> q(n);
        q[n-1] = 1;
        for(int j = n-1; j >= 1; j--){
            q[j-1] = x[i]*q[j]+f[j];
        }
        ModInt coef = y[i]*prod.inv();
        for(int j = 0; j < n; j++) ans[j] += coef*q[j];
    }
    return ans;
}

