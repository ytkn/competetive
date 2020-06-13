#include <iostream>
#include <vector>

using namespace std;

const int N_MAX = 200000;
int N;
bool used[N_MAX];
int idx[N_MAX];
vector<int> vs;
vector<int> buf;
vector<int> G[N_MAX];
vector<int> G_inv[N_MAX];
vector<vector<int>> ans;

void clear(){
    for(int i = 0; i < N; i++) used[i] = false;
}

void dfs1(int v){
    used[v] = true;
    for(int i = 0; i < G[v].size(); i++){
        if(!used[G[v][i]]) dfs1(G[v][i]);
    }
    vs.push_back(v);
}

void dfs2(int v, int k){
    used[v] = true;
    idx[v] = k;
    for(int i = 0; i < G_inv[v].size(); i++){
        if(!used[G_inv[v][i]]) dfs2(G_inv[v][i], k);
    }
    buf.push_back(v);
}

void scc(){
    for(int i = 0; i < N; i++){
        if(!used[i]) dfs1(i);
    }
    clear();
    int cur = 0;
    for(int i = vs.size()-1; i >= 0; i--){
        if(!used[vs[i]]) {
            dfs2(vs[i], cur);
            cur++;
            ans.push_back(buf);
            buf.clear();
        }
    }
}