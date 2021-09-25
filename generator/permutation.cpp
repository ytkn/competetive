#include <algorithm>
#include <random>
#include <vector>

using namespace std;

vector<int> gen_permutation(int n) {
    random_device seed_gen;
    mt19937 engine(seed_gen());
    vector<int> ans(n);
    for (int i = 0; i < n; i++) ans[i] = i;
    shuffle(ans.begin(), ans.end(), engine);
    return ans;
}