#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int INF =  100000000;

struct edge {int to, cap, rev;};

/**
 * verified: https://yukicoder.me/submissions/660443
 */
class Dinic{
    public:
        Dinic(int n){
            N = n;
            G = vector<vector<edge>>(n, vector<edge>());
            level = vector<int>(n, -1);
            iter = vector<int>(n, 0);
        }

        void add_edge(int from, int to, int cap){
            G[from].push_back((edge{to, cap, (int)G[to].size()}));
            G[to].push_back((edge{from, 0, (int)G[from].size()-1}));
        }

        int max_flow(int s, int t){
            int flow = 0;
            while(true){
                bfs(s);
                if(level[t] < 0) return flow;
                clear_iter();
                int f;
                while(f = dfs(s, t, INF) > 0){
                    flow += f;
                }
            }
        }

    private:
        vector<vector<edge>> G;
        vector<int> level;
        vector<int> iter;
        int N;
        void clear_level(){
            for(int i = 0; i < N; i++) level[i] = -1;
        }
        void clear_iter(){
            for(int i = 0; i < N; i++) iter[i] = 0;
        }

        int dfs(int v, int t, int f){
            if(v == t) return f;
            for(int &i = iter[v]; i < G[v].size(); i++){
                edge &e = G[v][i];
                if(e.cap > 0 && level[v] < level[e.to]){
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

        void bfs(int s){
            clear_level();
            queue<int> que;
            level[s] = 0;
            que.push(s);
            while(!que.empty()){
                int v = que.front();
                que.pop();
                for(edge e : G[v]){
                    if(e.cap > 0 && level[e.to] < 0){
                        level[e.to] = level[v]+1;
                        que.push(e.to);
                    }
                }
            }
        }
};