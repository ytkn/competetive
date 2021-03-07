#include <vector>
#include <functional>

using namespace std;

/**
 * gがDAGのとき: トポロジカルソートしてorderに結果を詰めてtrueを返します。
 * gがDAGのでないとき: falseを返します。
 * 自己辺はないことを前提として動きます。
 * verified(DAGの場合のみ): https://atcoder.jp/contests/dp/tasks/dp_g
 * verified(DAGの両方): https://yukicoder.me/submissions/614434
 */ 
bool topological_sort(vector<vector<int>> g, vector<int> &order){
    int n = g.size();
    order.clear();
    vector<bool> used(n, false);
    function<void(int)> dfs = [&](int v){
        used[v] = true;
        for(int to : g[v]){
            if(!used[to]) dfs(to);
        }
        order.push_back(v);
    };
    for(int v = 0; v < n; v++){
        if(!used[v]) dfs(v);
    }
    reverse(order.begin(), order.end());
    vector<int> inv_order(n);
    for(int i = 0; i < n; i++) inv_order[order[i]] = i;
    for(int v = 0; v < n; v++){
        for(int u : g[v]){
            if(inv_order[v] > inv_order[u]) return false;
        }
    }
    return true;
}
