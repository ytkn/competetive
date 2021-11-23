#include <random>
#include <algorithm>
#include "convex_hull_trick.hpp"
#include "gtest/gtest.h"

random_device rnd;
mt19937 mt(rnd());

int randint(const int l, const int r){
    return mt()%(r - l) + l;
}

int naive_min(int x, vector<int> p, vector<int> q){
    int n = p.size();
    vector<int> evals(n);
    for(int i = 0; i < n; i++) evals[i] = p[i]*x+q[i];
    return *min_element(evals.begin(), evals.end());
}

void run(){
    int n = 100;
    vector<int> p(n), q(n);
    auto cht = ConvexHullTrick<int>();
    for(int i = 0; i < n; i++){
        p[i] = -(100+i);
        q[i] = randint(100, 200);
        cht.add_line(p[i], q[i]);
    }
    
    for(int x = 0; x <= 100; x++){
        cht.proceed(x);
        ASSERT_EQ(cht.get_min(), naive_min(x, p, q));
    }
}

TEST(convex_hull_trick, get_min) {
    int n_exec = 100;
    while(n_exec--) run();
}