#include <vector>
#include <queue>

using namespace std;

typedef long long ll;
typedef pair<ll, int> P;

const ll INF = 1e18;

struct edge{
    int to;
    ll cap, cost;
    int rev;
};

/**
 * 負のコストの辺がない場合のみ使える
 */
class MinCostFlow{
    public:
        int V;  // 頂点数
        vector<vector<edge>> G;
        MinCostFlow(int v){
            V = v;
            G = vector<vector<edge>>(v, vector<edge>());
            dist = vector<ll>(v);
            h = vector<ll>(v);
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
                priority_queue<P, vector<P>, greater<P>> que;
                que.push(P(0, s));
                while(!que.empty()){
                    P top = que.top(); que.pop();
                    int v = top.second;
                    ll d = top.first;
                    if(dist[v] != d) continue;
                    for(int i = 0; i < G[v].size(); i++){
                        edge &e = G[v][i];
                        if(e.cap > 0 && dist[e.to] > dist[v]+e.cost+h[v]-h[e.to]){
                            dist[e.to] = dist[v]+e.cost+h[v]-h[e.to];
                            prevv[e.to] = v;
                            preve[e.to] = i;
                            que.push(P(dist[e.to], e.to));
                        }
                    }
                }
                
                if(dist[t] == INF){
                    return -1;
                }
                for(int i = 0; i < V; i++) h[i] += dist[i];
                ll d = f;
                for(int v = t; v != s; v = prevv[v]){
                    d = min(d, G[prevv[v]][preve[v]].cap);
                }
                f -= d;
                res += d*h[t];
                for(int v = t; v != s; v = prevv[v]){
                    edge &e = G[prevv[v]][preve[v]];
                    e.cap -= d;
                    G[v][e.rev].cap += d;
                }
            }
            return res;
        }

    private:
        vector<ll> dist, h;
        vector<int> prevv, preve;
};
