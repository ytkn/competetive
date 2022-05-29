#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/**
 * verified: https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=6665000#1 
 */
int edit_distance(string s, string t){
    int n = s.size(), m = t.size();
    auto dp = vector<vector<int>>(n+1, vector<int>(m+1, n+m));
    for(int i = 0; i <= n; i++) dp[i][0] = i;
    for(int j = 0; j <= m; j++) dp[0][j] = j;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int x = s[i] == t[j] ? 0 : 1;
            dp[i+1][j+1] = min({dp[i][j]+x, dp[i+1][j]+1, dp[i][j+1]+1});
        }
    }
    return dp[n][m];
}