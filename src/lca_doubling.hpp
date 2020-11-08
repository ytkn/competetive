#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
typedef long long ll;

/**
 * 多分大丈夫
 **/
class Lca{
    public:
        vector<int> depth;
        vector<vector<int>> parent;
        vector<vector<int>> G;
        int root;
        int n;
        const int N_LOG_MAX = 25;
        bool initialized = false;

        Lca(vector<vector<int>> g, int _root){
            n = g.size();
            G = g;
            root = _root;
            parent = vector<vector<int>>(N_LOG_MAX, vector<int>(n));
            depth = vector<int>(n, 0);
        }

        void init(){
            initialized = true;
            dfs(root, -1, 0);
            for(int i = 0; i < N_LOG_MAX-1; i++){
                for(int v = 0; v < n; v++){
                    if(parent[i][v] < 0) parent[i+1][v] = -1;
                    else parent[i+1][v] = parent[i][parent[i][v]];
                }
            }
        }

        int lca(int u, int v){
            assert(initialized);
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

    private:
        void dfs(int v, int p, int d){
            parent[0][v] = p;
            depth[v] = d;
            for(int i = 0; i < G[v].size(); i++){
                if(G[v][i] != p) dfs(G[v][i], v, d+1); 
            }
        }
};
