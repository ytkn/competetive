#include <vector>

using namespace std;

template<typename T>
struct ReRooting {
    int n;
    T(*e)();
    T(*merge)(T, T);
    T(*f)(T, int);
    T(*g)(T, int);
    vector<vector<int>> G;
    vector<vector<T>> dp;
    ReRooting(int n, T(*e)(), T(*merge)(T, T), T(*f)(T, int), T(*g)(T, int)): n(n), e(e), merge(merge), f(f), g(g) {
        dp.resize(n);
        G.resize(n);
    }
    ReRooting(vector<vector<int>> G, T(*e)(), T(*merge)(T, T), T(*f)(T, int), T(*g)(T, int)): n(G.size()), G(g), e(e), merge(merge), f(f), g(g) {
        dp.resize(n);
    }
    void add_edge(int u, int v){
        G[u].push_back(v);
        G[v].push_back(u);
    }
    T dfs1(int v, int p){
        T ans = e();
        for(int i = 0; i < G[v].size(); i++){
            int u = G[v][i];
            if(u == p) continue;
            dp[v][i] = dfs1(u, v);
            ans = merge(ans, dp[v][i]);
        }
        return g(ans, v);
    }
    void dfs2(int v, int p, T from_par){
        int deg = G[v].size();
        for(int i = 0; i < deg; i++){
            if(G[v][i] == p){
                dp[v][i] = from_par;
                break;
            }
        }
        vector<T> from_right(deg+1, e());
        for(int i = deg-1; i >= 0; i--){
            from_right[i] = merge(from_right[i+1], f(dp[v][i], G[v][i]));
        }
        T from_left = e();
        for(int i = 0; i < deg; i++){
            int u = G[v][i];
            if(u != p){
                T x = merge(from_left, from_right[i+1]);
                dfs2(u, v, g(x, v));
            }
            from_left = merge(from_left, f(dp[v][i], G[v][i]));
        }
    }
    vector<T> solve(int r = 0){
        for(int i = 0; i < n; i++) dp[i].assign(G[i].size(), e());
        dfs1(r, -1);
        dfs2(r, -1, e());
        vector<T> ans(n, e());
        for(int v = 0; v < n; v++){
            for(int i = 0; i < G[v].size(); i++){
                ans[v] = merge(ans[v], f(dp[v][i], G[v][i]));
            }
            ans[v] = g(ans[v], v);
        }
        return ans;
    }
};
