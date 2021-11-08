#include <vector>

using namespace std;
typedef long long ll;

/**
 * 置換操作 
 * permutation: (0, 1, ..., n-1)がpermutationに移るような置換操作の意味
 */
vector<int> operate(vector<int> prev, vector<int> permutation){
    int n = permutation.size();
    vector<int> ans(n);
    for(int i = 0; i < n; i++){
        ans[i] = prev[permutation[i]];
    }
    return ans;
}

/**
 * 置換操作の累乗
 */
vector<int> pow(vector<int> a, ll n) {
	vector<int> ans;
    for(int i = 0; i < a.size(); i++) ans.push_back(i);
	vector<int> tmp = a;
	for (int i = 0; i <= 60; i++) {
		ll m = (ll)1 << i;
		if (m & n) {
		    ans = operate(ans, tmp);
		}
		tmp = operate(tmp, tmp);
	}
	return ans;
}
