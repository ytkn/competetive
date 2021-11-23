#include "generator_utils.cpp"
#include "ford_fulkerson.hpp"
#include "gtest/gtest.h"
#include "naive_flow.cpp"

void run(){
    int n = 15;
    int n_edges = 100;
    vector<int> a, b, c;
    auto mf = FordFolkerson<int>(n);
    for(int i = 0; i < n_edges; i++){
        int u = randint(0, n);
        int v = randint(0, n);
        while(u == v) v = randint(0, n);
        int cap = randint(1, 10);
        a.push_back(u);
        b.push_back(v);
        c.push_back(cap);
        mf.add_edge(u, v, cap);
    }
    int s = 0, t = n-1;
    ASSERT_EQ(naive_flow(n, s, t, a, b, c), mf.max_flow(s, t));
}

TEST(ford_fulkerson, max_flow) {
    int n_exec = 10;
    while(n_exec--) run();
}