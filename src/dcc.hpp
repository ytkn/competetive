#include <iostream>
#include <vector>
#include <set>

#define N_MAX 200000

using namespace std;
typedef pair<int, int> P;

struct edge{
    int from, to;
};

/**
 * 動くか不明 
 */
class dcc{
    public:
        dcc(vector<edge> v, int size){
            G = vector<vector<int>>(size);
            used = vector<bool>(size, false);
            col = vector<int>(size, 1);
            num = vector<int>(size, -1);
            for(auto iter = v.begin(); iter != v.end(); iter++){
                int from = iter->from;
                int to = iter->to;
                G[from].push_back(to);
                G[to].push_back(from);
            }
            cur = -1;
            N = size;
        }

        vector<vector<int>> G;
        int N;
        vector<edge> run(){
            vector<edge> bridges;
            dfs(0, -1);
            clear();
            paint(0, -1, bridges);
            return bridges;
        }
    private:
        vector<bool> used;
        vector<int> col;
        vector<int> num;
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