#include "rollback_unionfind.hpp"
#include "unionfind.hpp"
#include "generator_utils.cpp"

#include "gtest/gtest.h"

const int UNITE = 1;
const int UNDO = -1;

TEST(rollback_unionfind, run) {
    int n = 100;
    int n_operations = 100;
    int n_queries = 100;
    vector<int> us, vs;
    RollbackUnionFind ruf(n);
    while(n_operations--){
        int kind = UNITE;
        if(!us.empty()){
            if(randint(0, 4) == 0) kind = UNDO;
        }
        if(kind == UNDO){
            ruf.undo();
            us.pop_back();
            vs.pop_back();
        }else{
            int u = randint(0, n);
            int v = randint(0, n);
            ruf.unionSet(u, v);
            us.push_back(u);
            vs.push_back(v);
        }
        UnionFind uf(n);
        int sz = us.size();
        for(int i = 0; i < sz; i++){
            uf.unionSet(us[i], vs[i]);
        }
        for(int i = 0; i < n_queries; i++){
            int u = randint(0, n);
            int v = randint(0, n);
            ASSERT_EQ(uf.findSet(u, v), ruf.findSet(u, v));
        }
    }
}
