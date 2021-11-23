#include <iostream>
#include <vector>

using namespace std;

const int INF = 100000000;

template<typename Cap>
struct edge {
    int to;
    Cap cap;
    int rev;
};

template<typename Cap>
class FordFolkerson{
    public:
        FordFolkerson(int n){
            N = n;
            G = vector<vector<edge<Cap>>>(n, vector<edge<Cap>>());
            used = vector<bool>(n, false);
        }

        void add_edge(int from, int to, Cap cap){
            G[from].push_back((edge<Cap>{to, cap, (int)G[to].size()}));
            G[to].push_back((edge<Cap>{from, 0, (int)G[from].size()-1}));
        }

        Cap max_flow(int s, int t){
            Cap flow = 0;
            while(true){
                clear_used();
                Cap f = dfs(s, t, INF);
                if(f == 0){
                    break;
                }
                flow += f;
            }
            return flow;
        }

    private:
        vector<vector<edge<Cap>>> G;
        vector<bool> used;
        int N;
        void clear_used(){
            for(int i = 0; i < N; i++) used[i] = false;
        }

        Cap dfs(int v, int t, Cap f){
            if(v == t) return f;
            used[v] = true;
            for(int i = 0; i < G[v].size(); i++){
                edge<Cap> &e = G[v][i];
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