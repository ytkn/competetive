#include <vector>

using namespace std;

typedef long long ll;

const ll INF = 1e+17;

struct edge{
    long from;
    long to;
    long cost;
};

//return
//true:if nagetive loop does not exist
//false:if negative loop exists
//d:result
bool bellmanford(vector<edge> es, ll d[], int s, int num_v){
    for(long i = 0; i < num_v; i++){
        d[i] = INF;
    }
    d[s] = 0;
    int cnt_loop = 0;
    while(true){
        cnt_loop++;
        bool update = false;
        for(int i = 0; i < es.size(); i++){
            edge e = es[i];
            if(d[e.from] != INF && d[e.from]+e.cost < d[e.to]){
                d[e.to] = d[e.from]+e.cost;
                update = true;
            }
        }
        if(!update) return true;
        else if(cnt_loop >= num_v) return false;
    }
}