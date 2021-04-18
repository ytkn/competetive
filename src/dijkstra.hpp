#include <vector>
#include <queue>

using namespace std;
typedef long long ll;
const ll INF = 1e+15;

typedef pair<ll, int> P;

struct edge{
    int to;
    ll cost;
};

vector<ll> dijkstra(int s, vector<vector<edge>> G){
    priority_queue<P, vector<P>, greater<P>> que;
    int n = G.size();
    vector<ll> d(n, INF);
    d[s] = 0;
    que.push(P(0, s));
    while(!que.empty()){
        P p = que.top();que.pop();
        int v = p.second;
        if(d[v] < p.first) continue;
        for(int i = 0; i < G[v].size(); i++){
            edge e = G[v][i];
            if(d[v] + e.cost < d[e.to]){
                d[e.to] = d[v] + e.cost;
                que.push(P(d[e.to], e.to));
            }
        }
    }
    return d;
}