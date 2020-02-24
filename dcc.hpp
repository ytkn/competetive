#include <iostream>
#include <vector>
#include <set>

#define N_MAX 200000

using namespace std;
typedef pair<int, int> P;

struct edge{
    int from, to;
};

class dcc{
    public:
        dcc(vector<edge> v, int size);
        vector<int> G[N_MAX];
        int N;
        vector<edge> run(){
            vector<edge> bridges;
            dfs(0, -1);
            clear();
            paint(0, -1, bridges);
            return bridges;
        }
    private:
        bool used[N_MAX];
        int col[N_MAX];
        int num[N_MAX];
        int cur;
        void dfs(int u, int p){
            used[u] = true;
            cur++;
            num[u] = cur;
            for(int i = 0; i < G[u].size(); i++){
                if(G[u][i] == p) continue;
                if(used[G[u][i]] && num[G[u][i]] < num[u] ){
                    col[u] = 1;
                    col[G[u][i]] = -1;
                }else if(!used[G[u][i]]){
                    dfs(G[u][i], u);
                }
            }
        }
        void paint(int u, int p, vector<edge> &v){
            used[u] = true;
            for(int i = 0; i < G[u].size(); i++){
                if(G[u][i] == p) continue;
                if(!used[G[u][i]]){
                    paint(G[u][i], u, v);
                    col[u] += col[G[u][i]];
                    if(col[G[u][i]] == 0){
                        v.push_back((edge){u, G[u][i]});
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

dcc::dcc(vector<edge> v, int size){
    for(auto iter = v.begin(); iter != v.end(); iter++){
        int from = iter->from;
        int to = iter->to;
        G[from].push_back(to);
        G[to].push_back(from);
    }
    for(int i = 0; i < size; i++){
        used[i] = false;
        col[i] = 0;
        num[i] = -1;
    }
    cur = -1;
    N = size;
}