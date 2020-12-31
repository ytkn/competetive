#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

typedef long long ll;

template <typename T>
struct matrix{
    int n, m;
    vector<vector<T>> dat;
    matrix(int n_, int m_){
        n = n_; m = m_;
        for(int i = 0; i < n; i++){
            dat.push_back(vector<T>(m));
        }
    }
    vector<T>& operator[](int x) {
        return dat[x];
	}
};

template <typename T>
bool prod(matrix<T> a, matrix<T> b, matrix<T> &ans){
    assert(a.m == b.n);
    for(int i = 0; i < a.n; i++){
        for(int j = 0; j < b.m; j++){
            ans.dat[i][j] = 0;
            for(int k = 0; k < b.n; k++){
                ans.dat[i][j] += (a.dat[i][k]*b.dat[k][j]);
            }
        }
    }
    return true;
}

template <typename T>
void copy_mat(matrix<T> a, matrix<T> &b){
    assert(a.n == b.n);
    assert(a.m == b.m);
    for(int i = 0; i < a.n; i++){
        for(int j = 0; j < a.m; j++){
            b.dat[i][j] = a.dat[i][j];
        }
    }
}

template <typename T>
void pow_mat(matrix<T> a, ll n, matrix<T> &ans){
    assert(n < ((ll)1<<61));
    matrix<T> buf(a.n, a.n);
    matrix<T> tmp(a.n, a.n);
    copy_mat(a, tmp);

    for(int i = 0; i < a.n; i++) {
        for(int j = 0; j < a.n; j++){
            ans.dat[i][j] = 0;
        }
        ans.dat[i][i] = 1;
    }
    
    for(int i = 0; i <= 60; i++){
        ll m = (ll)1 << i;
        if(m&n){
            prod(tmp, ans, buf);
            copy_mat(buf, ans);
        }
        prod(tmp, tmp, buf);
        copy_mat(buf, tmp);
    }
}

template <typename T>
void print_mat(matrix<T> a){
    for(int i = 0; i < a.n; i++){
        for(int j = 0; j < a.m; j++){
            cout << a.dat[i][j] << ' ';
        }
        cout << endl;
    }
}

/**
 * I+a+...+a^nを求めます(ちゃんと検証していないのであってないかも) 
 */ 
template<typename T>
void sum_pow(matrix<T> a, ll n, matrix<T> &ans){
    assert(a.n == a.m);
    assert(a.n == ans.n);
    assert(a.n == ans.m);
    matrix<T> A(2*a.n, 2*a.n);
    for(int i = 0; i < a.n; i++){
        for(int j = 0; j  < a.n; j++){
            A[i][j] = a[i][j];
            if(i == j){
                A[i+a.n][j] = 1;
                A[i+a.n][j+a.n] = 1;
            }
        }
    }
    matrix<T> B(2*a.n, a.n);
    for(int i = 0; i < a.n; i++){
        B[i][i] = 1;
    }
    matrix<T> S(2*a.n, a.n);
    matrix<T> buf(2*a.n, 2*a.n);
    pow_mat(A, n+1, buf);
    prod(buf, B, S);
    for(int i = 0; i < a.n; i++){
        for(int j = 0; j < a.n; j++){
            ans[i][j] = S[i+a.n][j];
        }
    }
}