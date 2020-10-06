#include <vector>

using namespace std;

typedef long long ll;

const int N_MAX = 1000;
const ll INF = 1e18;

struct edge{
    int to;
    ll cap, cost;
    int rev;
};

class MinCostFlow{
    public:
        int V;  // 頂点数
        vector<vector<edge>> G;
        MinCostFlow(int v){
            V = v;
            G = vector<vector<edge>>(v, vector<edge>());
            dist = vector<ll>(v);
            preve = vector<int>(v);
            prevv = vector<int>(v);
        }
        void add_edge(int from, int to, ll cap, ll cost){
            G[from].push_back((edge){to, cap, cost, G[to].size()});
            G[to].push_back((edge){from, 0, -cost, G[from].size()-1});
        }

        ll min_cost_flow(int s, int t, int f){
            ll res = 0;
            while(f > 0){
                fill(dist.begin(), dist.end(), INF);
                dist[s] = 0;
                bool update = true;
                while(update){
                    update = false;
                    for(int v = 0; v < V; v++){
                        if(dist[v] == INF) continue;
                        for(int i = 0; i < G[v].size(); i++){
                            edge &e = G[v][i];
                            if(e.cap > 0 && dist[e.to] > dist[v]+e.cost){
                                dist[e.to] = dist[v]+e.cost;
                                prevv[e.to] = v;
                                preve[e.to] = i;
                                update = true;
                            }
                        }
                    }
                }
                if(dist[t] == INF){
                    return -1;
                }
                ll d = f;
                for(int v = t; v != s; v = prevv[v]){
                    d = min(d, G[prevv[v]][preve[v]].cap);
                }
                f -= d;
                res += d*dist[t];
                for(int v = t; v != s; v = prevv[v]){
                    edge &e = G[prevv[v]][preve[v]];
                    e.cap -= d;
                    G[v][e.rev].cap += d;
                }
            }
            return res;
        }

    private:
        vector<ll> dist;
        vector<int> prevv, preve;
};
