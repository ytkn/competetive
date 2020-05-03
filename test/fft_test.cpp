#include "fft.hpp"
#include <vector>

#include "gtest/gtest.h"

typedef long long ll;
const double eps = 1e-5;

vector<double> simple_multiply(vector<double> f, vector<double> g){
    int fn = f.size();
    int gn = g.size();
    int n = fn+gn-1;
    vector<double> ans(n);
    for(int i = 0; i < fn; i++){
        for(int j = 0; j < gn; j++){
            ans[i+j] += f[i]*g[j];
        }
    }
    return ans;
}

void run(vector<double> f, vector<double> g){
    auto result = multiply(f, g);
    auto truth = simple_multiply(f, g);
    for(int i = 0; i < truth.size(); i++){
        ASSERT_TRUE(abs(result[i]-truth[i]) < eps);
    }
}

TEST(fft, multiply) {
    vector<double> v = {2.0, 1.0};
    vector<double> u = {1.0, 3.0, 4.0, 1.0};
    vector<double> v_small(10, 1.0);
    vector<double> v_middle(100, 1.0);
    vector<double> v_large(1000, 1.0);
    run(u, v);
    run(v_small, v_small);
    run(v_middle, v_middle);
    run(v_large, v_large);
}
