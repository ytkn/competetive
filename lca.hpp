#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

const int N_MAX = 160000;
const int N_LOG_MAX = 25;
vector<int> G[N_MAX];
int root;

int parent[N_LOG_MAX][N_MAX];
int depth[N_MAX];

void dfs(int v, int p, int d){
    parent[0][v] = p;
    depth[v] = d;
    for(int i = 0; i < G[v].size(); i++){
        if(G[v][i] != p) dfs(G[v][i], v, d+1); 
    }
}

void init(int V){
    dfs(root, -1, 0);
    for(int i = 0; i < N_LOG_MAX-1; i++){
        for(int v = 0; v < V; v++){
            if(parent[i][v] < 0) parent[i+1][v] = -1;
            else parent[i+1][v] = parent[i][parent[i][v]];
        }
    }
}

int lca(int u, int v){
    if(depth[u] > depth[v]) swap(u, v);
    for(int i = 0; i < N_LOG_MAX; i++){
        if((depth[v] - depth[u]) >> i & 1){
            v = parent[i][v];
        }
    }
    if(u == v) return u;
    for(int i = N_LOG_MAX-1; i >= 0; i--){
        if(parent[i][u] != parent[i][v]) {
            u = parent[i][u];
            v = parent[i][v];
        }
    }
    return parent[0][u];
}