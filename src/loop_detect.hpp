#include <vector>

using namespace std;

vector<int> G_in[100000];
vector<int> G_out[100000];
int cnt_in[100000];
int cnt_out[100000];
bool used[100000];

void dfs(int v){
    used[v] = false;
    for(int from : G_in[v]){
        cnt_out[from]--;
        if(cnt_out[from] == 0 && used[from]) dfs(from);
    }
    for(int to : G_out[v]){
        cnt_in[to]--;
        if(cnt_in[to] == 0 && used[to]) dfs(to);        
    }
}

bool loop_detect(int n_vertex){
    for(int i = 0; i < n_vertex; i++) used[i] = true;
    for(int i = 0; i < n_vertex; i++) cnt_in[i] = G_in[i].size();
    for(int i = 0; i < n_vertex; i++) cnt_out[i] = G_out[i].size();
    for(int i = 0; i < n_vertex; i++){
        if(cnt_in[i] == 0 || cnt_out[i] == 0){
            if(used[i]) dfs(i);
        }
    }
    for(int i = 0; i < n_vertex; i++) {
        if(used[i]) return true;
    }
    return false;
}