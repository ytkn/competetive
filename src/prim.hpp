#include <vector>
#include <queue>

using namespace std;
typedef long long ll;
typedef pair<int, int> P;

struct edge{
    int to;
    ll cost;
};

ll prim(vector<edge> G[], int s){
    vector<bool> used(s, false);
    priority_queue<P, vector<P>, greater<P>> que;
    ll ans = 0;
    //init tree
    for(int i = 0; i < s; i++){
        used[i] = false;
    }
    used[0] = true;
    for(int i = 0; i < G[0].size(); i++){
        que.push(P(G[0][i].cost, G[0][i].to));
    }
    
    while(!que.empty()){
        P top = que.top();
        que.pop();
        if(!used[top.second]){
            ans += top.first;
            used[top.second] = true;
            for(int i = 0; i < G[top.second].size(); i++){
                que.push(P(G[top.second][i].cost, G[top.second][i].to));
            }
        }
    }
    return ans;
}