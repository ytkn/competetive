#include <vector>
#include <random>
#include <cassert>
#include <set>
#include "unionfind.hpp"

using namespace std;

vector<vector<int>> gen_tree(int n){
    random_device rnd;
    mt19937 mt(rnd());
    UnionFind uf(n);
    vector<vector<int>> tree(n);
    auto add_edge = [&](int u, int v){
        if(u == v) return;
        if(u > v) swap(u, v);
        if(uf.findSet(u, v)) return;
        tree[u].push_back(v);
        tree[v].push_back(u);
        uf.unionSet(u, v);
    };
    while(uf.size(0) != n){
        int u = mt()%n;  
        int v = mt()%n;
        if(u == v) continue;
        add_edge(u, v);
    }
    return tree;
}

vector<vector<int>> gen_undirected(int n, int m, bool is_connected){
    vector<vector<int>> g(n);
    int rem = m;
    if(is_connected){
        assert(m >= n-1);
        g = gen_tree(n);
        rem -= n-1;
    }
    set<pair<int, int>> used;
    for(int i = 0; i < n; i++){
        for(int j: g[i]){
            if(i < j) used.insert(make_pair(i, j));
        }
    }
    auto add_edge = [&](int u, int v){
        if(u == v) return;
        if(u > v) swap(u, v);
        if(used.count(make_pair(u, v))) return;
        g[u].push_back(v);
        g[v].push_back(u);
        used.insert(make_pair(u, v));
        rem--;
    };
    random_device rnd;
    mt19937 mt(rnd());
    while(rem){
        int u = mt()%n;  
        int v = mt()%n;
        if(u == v) continue;
        add_edge(u, v);
    }
    return g;
}