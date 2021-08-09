#include <vector>

using namespace std;

class LoopDetect{
    public:
    int n;
    vector<vector<int>> g;
    vector<vector<int>> g_in;
    vector<bool> used;
    vector<int> cnt_in;
    vector<int> cnt_out;
    LoopDetect(vector<vector<int>> g): g(g){
        n = g.size();
        used.resize(n);
        cnt_in.resize(n);
        cnt_out.resize(n);
        g_in.resize(n);
        for(int i = 0; i < n; i++){
            for(int to: g[i]) g_in[to].push_back(i);
        }
        for(int i = 0; i < n; i++) used[i] = true;
        for(int i = 0; i < n; i++) cnt_in[i] = g_in[i].size();
        for(int i = 0; i < n; i++) cnt_out[i] = g[i].size();
    };

    void dfs(int v){
        used[v] = false;
        for(int from : g_in[v]){
            cnt_out[from]--;
            if(cnt_out[from] == 0 && used[from]) dfs(from);
        }
        for(int to : g[v]){
            cnt_in[to]--;
            if(cnt_in[to] == 0 && used[to]) dfs(to);        
        }
    }

    bool loop_detect(){
        for(int i = 0; i < n; i++){
            if(cnt_in[i] == 0 || cnt_out[i] == 0){
                if(used[i]) dfs(i);
            }
        }
        for(int i = 0; i < n; i++) {
            if(used[i]) return true;
        }
        return false;
    }
};