#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;


// calc ceil(a/b) 
template<typename T>
T ceil_div(T a, T b){
    return (a+b-1)/b;
}

/**
 * y*y <= xを満たす最大の非負整数yを返します
 */ 
long long floor_sqrt(long long x){
    long long sq = sqrt(x)+0.1;
    if(sq*sq > x) sq--;
    return sq;
}

/**
 * nの約数の個数を数えます(O(N^(1/2)))
 */ 
int count_divs(long long n){
    int ans = 0;
    for(long long x = 1; x*x <= n; x++){
        if(n%x == 0){
            ans++;
            if(x*x != n) ans++;
        }
    }
    return ans;
}

// smallest non negative integer r which satisfies (a-r)%b == 0
template<typename T>
T pos_rem(T a, T b){
    assert(b != 0);
    if(b > 0){
        return ((a%b)+b)%b;
    }
    b = -b;
    return ((a%b)+b)%b;
}

template<typename T>
vector<T> add_vector(vector<T> u, vector<T> v){
    assert(u.size() == v.size());
    int n = u.size();
    vector<T> ans(n);
    for(int i = 0; i < n; i++) ans[i] = u[i]+v[i];
    return ans;
}

template<typename T>
vector<T> pointwise_product(vector<T> u, vector<T> v){
    assert(u.size() == v.size());
    int n = u.size();
    vector<T> ans(n);
    for(int i = 0; i < n; i++) ans[i] = u[i]*v[i];
    return ans;
}

template<typename T>
void print_vector(vector<T> v, char delimiter=' '){
    for(int i = 0; i+1 < v.size(); i++) cout << v[i] << delimiter;
    cout << v.back() << endl;
}

template<typename T>
vector<T> naive_convolution(vector<T> u, vector<T> v){
    int n = u.size(), m = v.size();
    vector<T> ans(n+m-1);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            ans[i+j] += u[i]*v[j];
        }
    }
    return ans;
}

/**
 * f(x) = g(x)*h(x) + r(x)となる(h(x), r(x))を求めます
 */ 
template<typename T>
pair<vector<T>, vector<T>> naive_divide(vector<T> f, vector<T> g){
    int n = f.size()-1;
    int m = g.size()-1;
    if(n < m) return make_pair(vector<T>(1, T(0)), f);
    int k = n-m;
    vector<T> h(k+1);
    T iv = T(1)/g[m];
    for(int i = k; i >= 0; i--){
        h[i] = f[i+m]*iv;
        for(int j = 0; j <= m; j++){
            f[i+j] -= g[j]*h[i];
        }
    }
    return make_pair(h, f);
}