#include <array>
#include <iostream>

#include "mod_int.hpp"

using namespace std;

template<typename T, int N, int M>
class Matrix {
    public:
    array<array<T, M>, N> dat;
    Matrix(T val) {
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                dat[i][j] = val;
            }
        }
    }

    Matrix(array<array<T, M>, N> dat): dat(dat){  }
    array<T, M>& operator[](int x) {
        return dat[x];
	}
};

template<typename T, int N, int M, int K>
Matrix<T, N, K> operator*(Matrix<T, N, M> a, Matrix<T, M, K> b){
    Matrix<T, N, K> c(T(0));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < K; j++){
            for(int k = 0; k < M; k++){
                c.dat[i][j] += a.dat[i][k]*b.dat[k][j];
            }
        }
    }
    return c;
}

template<typename T, int N>
Matrix<T, N, N> operator^(Matrix<T, N, N> m, long long r){
    Matrix<T, N, N> ans(T(0));
    for(int i = 0; i < N; i++) ans[i][i] = T(1);
    while (r > 0) {
        if (r&1) ans = (ans*m);
        m = (m*m);
        r >>= 1;
    }
    return ans;
}

template <typename T, int N, int M>
void print_mat(Matrix<T, N, M> a){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cout << a.dat[i][j] << ' ';
        }
        cout << endl;
    }
}

template <typename T, int N, int M>
ostream& operator<<(ostream& os, const Matrix<T, N, M>& m){
    print_mat<T, N, M>(m);
    return os;
}

// x^0 + x^1 + ... + x^n-1
ModInt sum_pow(ModInt x, ll n){
    Matrix<ModInt, 2, 2> m(ModInt(0));
    m.dat[0][0] = x; m.dat[0][1] = 0;
    m.dat[1][0] = 1; m.dat[1][1] = 1;
    Matrix<ModInt, 2, 1> v(ModInt(0));
    v.dat[0][0] = 1;
    v.dat[1][0] = 0;
    Matrix<ModInt, 2, 2> p = m^n;
    Matrix<ModInt, 2, 1> p_sum = p*v;
    return p_sum.dat[1][0];
}