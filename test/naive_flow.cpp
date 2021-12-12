#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

/**
 * s-tカットを全探索することでs-t最大フローを求めます
 */ 
template<typename Cap>
int naive_flow(int n, int s, int t, vector<int> a, vector<int> b, vector<Cap> c){
    int n_edges = a.size();
    assert(b.size() == n_edges);
    assert(c.size() == n_edges);
    int mask = (1<<n)-1 - (1<<s) - (1<<t);
    vector<Cap> cut_capacities;
    for(int s_side = mask; s_side >= 0; s_side = (s_side-1)&mask){
        vector<bool> is_s_side(n, false);
        is_s_side[s] = true;
        for(int v = 0; v < n; v++){
            if(s_side&(1<<v)) is_s_side[v] = true;
        }
        Cap cap = 0;
        for(int i = 0; i < n_edges; i++){
            if(is_s_side[a[i]] && !is_s_side[b[i]]) cap += c[i];
        }
        cut_capacities.push_back(cap);
        if(s_side == 0) break;
    }
    return *min_element(cut_capacities.begin(), cut_capacities.end());
}