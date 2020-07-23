#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
const ll MOD = 1000000007;

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
};

template <typename T>
bool prod(matrix<T> a, matrix<T> b, matrix<T> &ans){
    if(a.m != b.n) return false;
    for(int i = 0; i < a.n; i++){
        for(int j = 0; j < a.m; j++){
            ans.dat[i][j] = 0;
            for(int k = 0; k < b.m; k++){
                ans.dat[i][j] += (a.dat[i][k]*b.dat[k][j])%MOD;
                ans.dat[i][j] %= MOD;
            }
        }
    }
    return true;
}

template <typename T>
void copy_mat(matrix<T> a, matrix<T> &b){
    for(int i = 0; i < a.n; i++){
        for(int j = 0; j < a.m; j++){
            b.dat[i][j] = a.dat[i][j];
        }
    }
}

template <typename T>
void pow(matrix<T> a, ll n, matrix<T> &ans){
    matrix<T> buf(a.n, a.n);
    matrix<T> tmp(a.n, a.n);
    copy_mat(a, tmp);

    for(int i = 0; i < a.n; i++) {
        for(int j = 0; j < a.n; j++){
            ans.dat[i][j] = 0;
        }
        ans.dat[i][i] = 1;
    }
    
    for(int i = 0; i <= 30; i++){
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