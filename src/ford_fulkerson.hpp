#include <iostream>
#include <vector>

using namespace std;

const int INF = 100000000;

struct edge {int to, cap, rev;};

class FordFolkerson{
    public:
        FordFolkerson(int n){
            N = n;
            G = vector<vector<edge>>(n, vector<edge>());
            used = vector<bool>(n, false);
        }

        void add_edge(int from, int to, int cap){
            G[from].push_back((edge{to, cap, (int)G[to].size()}));
            G[to].push_back((edge{from, 0, (int)G[from].size()-1}));
        }

        int max_flow(int s, int t){
            int flow = 0;
            while(true){
                clear_used();
                int f = dfs(s, t, INF);
                if(f == 0){
                    break;
                }
                flow += f;
            }
            return flow;
        }

    private:
        vector<vector<edge>> G;
        vector<bool> used;
        int N;
        void clear_used(){
            for(int i = 0; i < N; i++) used[i] = false;
        }

        int dfs(int v, int t, int f){
            if(v == t) return f;
            used[v] = true;
            for(int i = 0; i < G[v].size(); i++){
                edge &e = G[v][i];
                if(!used[e.to] && e.cap > 0){
                    int d = dfs(e.to, t, min(f, e.cap));
                    if(d > 0){
                        e.cap -= d;
                        G[e.to][e.rev].cap += d;
                        return d;
                    }
                }
            }
            return 0;
        }
};