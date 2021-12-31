#include <queue>
#include "euler_tour.hpp"
#include "graph.cpp"
#include "bit.hpp"

#include "gtest/gtest.h"

vector<int> calc_depth(vector<vector<int>> tree, int root){
    int n = tree.size();
    vector<bool> seen(n);
    vector<int> depth(n);
    queue<int> que;
    auto set_depth = [&](int v, int d){
        seen[v] = true;
        depth[v] = d;
        que.push(v);
    };
    set_depth(root, 0);
    while(!que.empty()){
        int v = que.front(); que.pop();
        for(int to: tree[v]){
            if(seen[to]) continue;
            set_depth(to, depth[v]+1);
        }
    }
    return depth;
}

void test_by_depth(vector<vector<int>> tree){
    int n = tree.size();
    int root = 0;
    auto depth = calc_depth(tree, root);
    auto et = EulerTour(tree, root);
    bit<int> bt(et.ord.size()+1);
    for(int i = 0; i < et.ord.size(); i++){
        int v = et.ord[i];
        if(et.in[v] == i) bt.add(i+1, 1);
        if(et.out[v] == i) bt.add(i+2, -1);
    }
    auto get_depth = [&](int v){
        return bt.sum(et.in[v]+1)-1;
    };
    for(int i = 0; i < n; i++){
        ASSERT_EQ(get_depth(i), depth[i]);
    }
}

TEST(euler_tour, depth) {
    for(int i = 0; i < 10; i++) {
        auto tree = gen_tree(100);
        test_by_depth(tree);
    }
}
