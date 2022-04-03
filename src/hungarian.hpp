#include <iostream>
#include <vector>
#include <cassert>

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

using namespace std;

/**
 * verified: https://judge.yosupo.jp/submission/84617
 */ 
template<typename T>
pair<T, vector<int>> solve_assignment(int n, vector<vector<T>> a, T inf){
    int m = 2*n+2;
    vector<bool> used_left(n), used_right(n);
    vector<vector<bool>> rev(n, vector<bool>(n, false));
    vector<T> h(m, T(0));
    vector<T> dist(m, inf);
    vector<int> prevv(m, -1);
    vector<bool> seen(m);
    int s = 0, t = 2*n+1;
    for(int f = 1; f <= n; f++){
        dist.assign(m, inf);
        seen.assign(m, false);
        prevv.assign(m, -1);
        dist[s] = T(0);
        int v = s;
        while(true){
            seen[v] = true;
            auto try_change = [&](int to, T cost){
                if(chmin(dist[to], dist[v]+cost+h[v]-h[to])){
                    prevv[to] = v;
                }
            };
            if(v == s){
                for(int to = 1; to <= n; to++){
                    int left_idx = to-1;
                    if(used_left[left_idx]) continue;
                    try_change(to, T(0));
                }
            }else if(v <= n){
                int left_idx = v-1;
                for(int to = n+1; to <= 2*n; to++){
                    int right_idx = to-(n+1);
                    if(rev[left_idx][right_idx]) continue;
                    try_change(to, a[left_idx][right_idx]);
                }
            }else{
                int right_idx = v-n-1;
                for(int to = 1; to <= n; to++){
                    int left_idx = to-1;
                    if(!rev[left_idx][right_idx]) continue;
                    try_change(to, -a[left_idx][right_idx]);
                }
                if(!used_right[right_idx]){
                    try_change(t, T(0));
                }
            }
            int nx = -1;
            T min_dist = inf;
            for(int i = 0; i < m; i++){
                if(!seen[i]){
                    if(chmin(min_dist, dist[i])) nx = i;
                }
            }
            if(nx == -1) break;
            v = nx;
        }
        for(int i = 0; i < m; i++){
            h[i] += dist[i];
        }
        int cur = t;
        while(cur != s){
            if(cur == t){
                int right_idx = prevv[cur]-(n+1);
                used_right[right_idx] = true;
            }else if(cur > n){
                int right_idx = cur-(n+1);
                int left_idx = prevv[cur]-1;
                rev[left_idx][right_idx] = true;
            }else{
                int left_idx = cur-1;
                if(prevv[cur] == s){
                    used_left[left_idx] = true;
                }else{
                    int right_idx = prevv[cur]-(n+1);
                    rev[left_idx][right_idx] = false;
                }
            }
            cur = prevv[cur];
        }
    }
    vector<int> ans(n);
    T sum = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(rev[i][j]) {
                ans[i] = j;
                sum += a[i][j];
            }
        }
    }
    return make_pair(sum, ans);
}
