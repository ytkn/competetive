#include <array>
#include <iostream>

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
