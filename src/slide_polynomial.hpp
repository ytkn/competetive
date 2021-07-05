#include <vector>
#include <atcoder/modint>
#include <atcoder/convolution>

using namespace std;

using mint = atcoder::modint998244353;
using ll = long long;
const ll MOD = 998244353;

#define N_MAX 300002
mint inv[N_MAX],fac[N_MAX],finv[N_MAX];

void init(){
    fac[0]=1;fac[1]=1;
    finv[0]=1;finv[1]=1;
    inv[1]=1;
    for(int i=2;i<N_MAX;i++){
        inv[i]=mint(MOD)-inv[MOD%i]*(MOD/i);
        fac[i]=fac[i-1]*(ll) i;
        finv[i]=finv[i-1]*inv[i];
    }
}

mint pow(mint a, ll n) {
    assert(n >= 0);
	mint ans = 1;
	mint tmp = a;
	for (int i = 0; i <= 60; i++) {
		ll m = (ll)1 << i;
		if (m & n) {
		ans *= tmp;
		}
		tmp *= tmp;
	}
	return ans;
}

/**
 * a0+a1*(x+c)^1+ ... + an*(x+c)^nの係数を求める
 */ 
vector<mint> slide_polynomial(vector<mint> a, int c){
    int n = a.size();
    vector<mint> u(n), v(n);
    for(int i = 0; i < n; i++) {
        u[i] = a[i]*fac[i];
        v[i] = pow(mint(c), n-i-1)*finv[n-i-1];
    }
    auto w = atcoder::convolution(u, v);
    vector<mint> ans(n);
    for(int i = 0; i < n; i++) ans[i] = finv[i]*w[i+n-1];
    return ans;
}