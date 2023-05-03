#include "fps.hpp"
#include "zeta_mobius.hpp"

/**
 * verified: https://judge.yosupo.jp/submission/137409
 */
vector<mint> subset_convolution(vector<mint> a, vector<mint> b, int n){
    assert(a.size() == (1<<n));
    assert(b.size() == (1<<n));
    vector<FPS> aa(1<<n, FPS(n+1, mint(0)));
    vector<FPS> bb(1<<n, FPS(n+1, mint(0)));
    for(int s = 0; s < (1<<n); s++){
        aa[s][__builtin_popcount(s)] = a[s];
        bb[s][__builtin_popcount(s)] = b[s];
    }
    aa = subset_zeta(aa, n);
    bb = subset_zeta(bb, n);
    vector<FPS> cc(1<<n, FPS(2*n+1, mint(0)));
    for(int s = 0; s < (1<<n); s++){
        cc[s] = aa[s]*bb[s];
    }
    auto c = subset_mobius(cc, n);
    vector<mint> ans(1<<n);
    for(int s = 0; s < (1<<n); s++){
        ans[s] = c[s][__builtin_popcount(s)];
    }
    return ans;
}
