#include <vector>

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

using namespace std;

template<typename T>
vector<vector<T>> vec2d(int n, int m, T v){
    return vector<vector<T>>(n, vector<T>(m, v));
}

int longest_common_sequence(vector<int> s, vector<int> t){
    int n = s.size(), m = t.size();
    auto dp = vec2d(n+2, m+2, 0);
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= m; j++){
            if(i < n && j < m && s[i] == t[j]){
                chmax(dp[i+1][j+1], dp[i][j]+1);
            }else{
                chmax(dp[i+1][j+1], dp[i][j]);
            }
            chmax(dp[i+1][j], dp[i][j]);
            chmax(dp[i][j+1], dp[i][j]);
        }
    }
    return dp[n][m];
}