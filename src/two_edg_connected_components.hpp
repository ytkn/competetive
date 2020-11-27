#include <iostream>
#include <vector>
#include <set>

#define N_MAX 200000

using namespace std;
typedef pair<int, int> P;

struct edge{
    int from, to;
};

/**
 * dfs木上の後退辺に対応するpathをimos法で塗っていく
 * 塗られなかった辺が橋となる
 * verified by ARC039 D
 */
class TwoEdgeConnectedComponents{
    public:
        TwoEdgeConnectedComponents(vector<edge> v, int size){
            G = vector<vector<int>>(size);
            used = vector<bool>(size, false);
            col = vector<int>(size, 0);
            depth = vector<int>(size, 0);
            for(edge e : v){
                int from = e.from;
                int to = e.to;
                G[from].push_back(to);
                G[to].push_back(from);
            }
            N = size;
        }

        vector<vector<int>> G;
        int N;
        vector<edge> run(){
            vector<edge> bridges;
            dfs(0, -1, 0);
            clear();
            paint(0, -1, bridges);
            return bridges;
        }
    private:
        vector<bool> used;
        vector<int> col;
        vector<int> depth;
        void dfs(int u, int p, int d){
            used[u] = true;
            depth[u] = d;
            for(int to : G[u]){
                if(to == p) continue;
                if(used[to] && depth[to] < depth[u]){
                    col[u]++;
                    col[to]--;
                }else if(!used[to]){
                    dfs(to, u, d+1);
                }
            }
        }

        void paint(int u, int p, vector<edge> &v){
            used[u] = true;
            for(int to : G[u]){
                if(to == p) continue;
                if(!used[to]){
                    paint(to, u, v);
                    col[u] += col[to];
                    if(col[to] == 0){
                        v.push_back((edge){u, to});
                    }
                }
            }
        }
        void clear(){
            for(int i = 0; i < N; i++){
                used[i] = false;
            }
        }
};