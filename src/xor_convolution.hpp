#include <vector>
#include <cassert>

using namespace std;

template<typename T>
vector<T> hadamard_transform_recursive(vector<T> v){
    int n = v.size();
    if(n == 1){
        return v;
    }
    assert(n%2 == 0);
    int m = n/2;
    vector<T> ans(n);
    vector<T> vl(m), vr(m);
    for(int i = 0; i < m; i++){
        vl[i] = v[i];
        vr[i] = v[i+m];
    }
    auto hl = hadamard_transform_recursive(vl);
    auto hr = hadamard_transform_recursive(vr);
    for(int i = 0; i < m; i++){
        ans[i] = hl[i]+hr[i];
        ans[i+m] = hl[i]-hr[i];
    }
    return ans;
}

template<typename T>
vector<T> hadamard_transform_inline(vector<T> v){
    int h = 1;
    while(h < v.size()){
        for(int i = 0; i < v.size(); i += h*2){
            for(int j = i; j < i+h; j++){
                T x = v[j];
                T y = v[j+h];
                v[j] = x+y;
                v[j+h] = x-y;
            }
        }
        h *= 2;
    }
    return v;
}

/**
 * verified: https://judge.yosupo.jp/submission/54638
 */ 
template<typename T>
vector<T> xor_convolution(vector<T> u, vector<T> v){
    assert(u.size() == v.size());
    int n = u.size();
    auto hu = hadamard_transform_inline(u);
    auto hv = hadamard_transform_inline(v);
    vector<T> w(n);
    for(int i = 0; i < n; i++) w[i] = (hu[i]*hv[i]);
    auto ans = hadamard_transform_inline(w);
    T one = 1;
    T n_inv = one/n;
    for(int i = 0; i < n; i++) ans[i] = ans[i]*n_inv;
    return ans;
}