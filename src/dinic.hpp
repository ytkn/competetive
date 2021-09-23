#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int INF =  100000000;

template<typename Cap>
struct edge {
    int to;
    Cap cap;
    int rev;
};

/**
 * verified: https://yukicoder.me/submissions/660443, https://atcoder.jp/contests/arc031/submissions/26061627
 */
template<typename Cap>
class Dinic{
    public:
        Dinic(int n){
            N = n;
            G = vector<vector<edge<Cap>>>(n, vector<edge<Cap>>());
            level = vector<int>(n, -1);
            iter = vector<int>(n, 0);
        }

        void add_edge(int from, int to, Cap cap){
            G[from].push_back(edge<Cap>{to, cap, (int)G[to].size()});
            G[to].push_back(edge<Cap>{from, 0, (int)G[from].size()-1});
        }

        Cap flow(int s, int t){
            Cap flow = 0;
            while(true){
                bfs(s);
                if(level[t] < 0) return flow;
                clear_iter();
                while(true){
                    Cap f = dfs(s, t, INF);
                    if(f == 0) break;
                    flow += f;
                }
            }
        }

    private:
        vector<vector<edge<Cap>>> G;
        vector<int> level;
        vector<int> iter;
        int N;
        void clear_level(){
            for(int i = 0; i < N; i++) level[i] = -1;
        }
        void clear_iter(){
            for(int i = 0; i < N; i++) iter[i] = 0;
        }

        Cap dfs(int v, int t, Cap f){
            if(v == t) return f;
            for(int &i = iter[v]; i < G[v].size(); i++){
                edge<Cap> &e = G[v][i];
                if(e.cap > 0 && level[v] < level[e.to]){
                    Cap d = dfs(e.to, t, min(f, e.cap));
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
                for(edge<Cap> e : G[v]){
                    if(e.cap > 0 && level[e.to] < 0){
                        level[e.to] = level[v]+1;
                        que.push(e.to);
                    }
                }
            }
        }
};