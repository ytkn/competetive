#include <atcoder/modint>
#include <atcoder/convolution>
#include <vector>

using namespace std;

using mint = atcoder::modint998244353;

/**
 * NOTE: qの末尾が0であってはならない.
 * for NTT-friendly modint
 */
mint bostan_mori(vector<mint> p, vector<mint> q, long long n){
    assert(p.back().val() != 0);
    int d = q.size()-1;
    assert(p.size() <= d);
    assert(q[0] == mint(1));
    if(n == 0){
        return p[0];
    }
    vector<mint> q_neg = q;
    for(int i = 1; i < (int)q.size(); i+=2) q_neg[i] *= -1;
    auto pq = atcoder::convolution(p, q_neg);
    auto qq = atcoder::convolution(q, q_neg);
    vector<mint> v((qq.size()+1)/2);
    for(int i = 0; i < qq.size(); i+=2){
        v[i/2] = qq[i];
    }
    vector<mint> u(n%2 == 0 ? (pq.size()+1)/2 : pq.size()/2);
    for(int i = 0; i < pq.size(); i++){
        if(n%2 == 0 && i%2 == 0){
            u[i/2] = pq[i];
        }else if(n%2 == 1 && i%2 == 1){
            u[i/2] = pq[i];
        }
    }
    return bostan_mori(u, v, n/2);
}

/**
 * s_n = s_{n-1}*c_0 + s_{n-2}*c_1 + ... + s_{n-d}*c_{d-1}
 * for NTT-friendly modint
 */
mint kth_element(vector<mint> c, vector<mint> s, long long k){
    int d = c.size();
    assert(s.size() == d);
    vector<mint> q(d+1);
    q[0] = 1;
    for(int i = 0; i < d; i++) q[i+1] = -c[i];
    auto pp = atcoder::convolution(s, q);
    vector<mint> p(d);
    for(int i = 0; i < d; i++) p[i] = pp[i];
    return bostan_mori(p, q, k);
}

/**
 * NOTE: qの末尾が0であってはならない
 */
template <class T, vector<T> (*multiply)(const vector<T>&, const vector<T>&)>
T bostan_mori(vector<T> p, vector<T> q, long long n){
    assert(p.back() != T(0));
    int d = q.size()-1;
    assert(p.size() <= d);
    assert(q[0] == T(1));
    if(n == 0){
        return p[0];
    }
    vector<T> q_neg = q;
    for(int i = 1; i < (int)q.size(); i+=2) q_neg[i] *= -1;
    vector<T> pq = multiply(p, q_neg);
    vector<T> qq = multiply(q, q_neg);
    vector<T> v((qq.size()+1)/2);
    for(int i = 0; i < qq.size(); i+=2){
        v[i/2] = qq[i];
    }
    vector<T> u(n%2 == 0 ? (pq.size()+1)/2 : pq.size()/2);
    for(int i = 0; i < pq.size(); i++){
        if(n%2 == 0 && i%2 == 0){
            u[i/2] = pq[i];
        }else if(n%2 == 1 && i%2 == 1){
            u[i/2] = pq[i];
        }
    }
    return bostan_mori<T, multiply>(u, v, n/2);
}

/**
 * s_n = s_{n-1}*c_0 + s_{n-2}*c_1 + ... + s_{n-d}*c_{d-1}
 */
template <class T, vector<T> (*multiply)(const vector<T>&, const vector<T>&)>
T kth_element(vector<T> c, vector<T> s, long long k){
    int d = c.size();
    assert(s.size() == d);
    vector<T> q(d+1);
    q[0] = T(1);
    for(int i = 0; i < d; i++) q[i+1] = -c[i];
    auto pp = multiply(s, q);
    vector<T> p(d);
    for(int i = 0; i < d; i++) p[i] = pp[i];
    return bostan_mori<T, multiply>(p, q, k);
}
