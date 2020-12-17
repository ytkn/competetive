#include <vector>

using namespace std;

typedef long long ll;

/**
 * 数列aが漸化式 a[n+k] = \sum_{i=0}^{i=k-1} {d[i]*a[i]}を満たし、
 * a[n] = \sum_{i=0}^{i=k-1} {x[i]*a[i]}であるとき、
 * a[n+1] = \sum_{i=0}^{i=k-1} {v[i]*a[i]}を満たすvを返します
 */
template<typename T>
vector<T> kitamasa_next(vector<T> x, vector<T> d){
    assert(x.size() == d.size());
    int k = x.size();
    vector<T> v(k);
    for(int i = 0; i <= k-2; i++) v[i+1] += x[i];
    for(int i = 0; i <= k-1; i++) v[i] += d[i]*x[k-1];
    return v;
}

/**
 * a[n] = \sum_{i=0}^{i=k-1} {x[i]*a[i]}のときに
 * a[2*n] = \sum_{i=0}^{i=k-1} {v[i]*a[i]}を満たすvを返します
 */
template<typename T>
vector<T> kitamasa_twice(vector<T> x, vector<T> d){
    assert(x.size() == d.size());
    int k = x.size();
    vector<vector<T>> u(k+1, vector<T>(k));
    vector<T> v(k);
    u[0] = x;
    for(int i = 1; i <= k-1; i++){
        u[i] = kitamasa_next(u[i-1], d);
    }
    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            v[j] += x[i]*u[i][j];
        }
    }
    return v;
}

/**
 * verified: https://atcoder.jp/contests/tdpc/tasks/tdpc_fibonacci
 * 参考: https://outline.hatenadiary.jp/entry/2020/07/02/205628
 * 数列aが漸化式 a[n+k] = \sum_{i=0}^{i=k-1} {d[i]*a[i]}を満たしているときに
 * その第m項を返します。
 * aは第k-1項目まで(0-indexed)を与えてください
 */
template<typename T>
T kitamasa(vector<T> a, vector<T> d, ll m){
    assert(a.size() == d.size());
    int k = a.size();
    if(m < k) return a[m];
    vector<ll> indices;
    ll tmp = m;
    indices.push_back(tmp);
    while(tmp != k){
        if(tmp%2 == 0 && tmp/2 >= k) tmp /= 2;
        else tmp--;
        indices.push_back(tmp);
    }
    reverse(indices.begin(), indices.end());
    vector<T> x = d;
    for(int i = 1; i < indices.size(); i++){
        if(indices[i-1]+1 == indices[i]){
            x = kitamasa_next(x, d);
        }else{
            x = kitamasa_twice(x, d);
        }
    }
    T ans = 0;
    for(int i = 0; i < k; i++){
        ans += x[i]*a[i];
    }
    return ans;
}