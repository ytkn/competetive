#include <vector>

using namespace std;

vector<int> tree_diameter(vector<vector<int>> g){
    int n = g.size();
    vector<bool> used(n, false);
    vector<int> dist(n);
    auto clear = [&](){
        for(int i = 0; i < n; i++) used[i] = false;
    };
    auto dfs = [&](auto&& f, int v, int d) -> void{
        used[v] = true;
        dist[v] = d;
        for(int to : g[v]){
            if(!used[to]) f(f, to, d+1);
        }
    };
    dfs(dfs, 0, 0);
    int s = 0;
    for(int i = 0; i < n; i++){
        if(s < dist[i]) s = i;
    }
    clear();
    dfs(dfs, s, 0);
    int t = 0;
    for(int i = 0; i < n; i++){
        if(t < dist[i]) t = i;
    }
    int v = t;
    vector<int> path;
    path.push_back(t);
    while(v != s){
        for(int to : g[v]){
            if(dist[to] == dist[v]-1) {
                v = to;
                break;
            }
        }
        path.push_back(v);
    }
    return path;
}

template<typename T>
struct edge{
    int to;
    T cost;
};

/**
 * verified: https://old.yosupo.jp/submission/45254
 */ 
template<typename T>
pair<vector<int>, T> tree_diameter(vector<vector<edge<T>>> g){
    int n = g.size();
    vector<bool> used(n, false);
    vector<T> dist(n);
    auto clear = [&](){
        for(int i = 0; i < n; i++) used[i] = false;
    };
    auto dfs = [&](auto&& f, int v, T d) -> void{
        used[v] = true;
        dist[v] = d;
        for(auto e : g[v]){
            if(!used[e.to]) f(f, e.to, d+e.cost);
        }
    };
    dfs(dfs, 0, 0);
    int s = 0;
    for(int i = 0; i < n; i++){
        if(dist[s] < dist[i]) s = i;
    }
    clear();
    dfs(dfs, s, 0);
    int t = 0;
    for(int i = 0; i < n; i++){
        if(dist[t] < dist[i]) t = i;
    }
    int v = t;
    vector<int> path;
    path.push_back(t);
    while(v != s){
        for(auto e : g[v]){
            if(dist[e.to] == dist[v]-e.cost) {
                v = e.to;
                break;
            }
        }
        path.push_back(v);
    }
    return make_pair(path, dist[t]);
}