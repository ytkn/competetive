#include <vector>
#include <random>

using namespace std;

vector<int> gen_array(int n, int l, int r){
    int d = r-l;
    random_device rnd;
    mt19937 mt(rnd());
    vector<int> ans(n);
    int x = mt();
    for(int i = 0; i < n; i++) ans[i] = l+(mt()%d);
    return ans;
}