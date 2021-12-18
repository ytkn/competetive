#include "cumsum_grid.hpp"
#include "array.cpp"
#include "generator_utils.cpp"
#include "mod_int.hpp"

#include "gtest/gtest.h"

void run_test(vector<vector<int>> grid){
    int n = grid.size(), m = grid[0].size();
    auto naive = [&](int il, int ir, int jl, int jr){
        int ans = 0;
        for(int i = il; i < min(ir, n); i++){
            for(int j = jl; j < min(jr, m); j++){
                ans += grid[i][j];
            }
        }
        return ans;
    };
    int n_query = 100;
    auto cumsum = CumsumGrid<int>(grid);
    while(n_query--){
        int il = randint(0, n+1), ir = randint(0, n+1);
        int jl = randint(0, m+1), jr = randint(0, m+1);
        ASSERT_EQ(cumsum.sum(il, ir, jl, jr), naive(il, ir, jl, jr));
    }
}

TEST(cumsum_grid, sum) {
    int n_test = 10;
    for(int i = 0; i < n_test; i++){
        int n = 50, m = 30;
        vector<vector<int>> grid(n);
        for(int j = 0; j < n; j++) grid[j] = gen_array(m, 0, 1000);
        run_test(grid);
    }
}

