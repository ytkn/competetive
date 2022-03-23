#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

const double eps = 1e-9;

template<typename T>
bool is_zero(T x){
    if constexpr (is_floating_point<T>::value){
        return abs(x) < eps;
    }else{
        return x == T(0);
    }
}

/**
 * verified: https://judge.yosupo.jp/submission/83411
 * returns: (solution, basis)
 */ 
template<typename T>
pair<vector<T>, vector<vector<T>>> solve_linear_equation(vector<vector<T>> A, vector<T> b){
    assert(!A.empty());
    int n = A.size(), m = A[0].size();
    assert(n == b.size());
    int rank = 0;
    vector<int> col_pivot(m, -1);
    for(int col = 0; col < m; col++){
        int pivot = -1;
        for(int row = rank; row < n; row++){
            if(!is_zero(A[row][col])){
                pivot = row;
                break;
            }
        }
        if(pivot == -1) continue;
        col_pivot[col] = rank;
        swap(A[rank], A[pivot]);
        swap(b[rank], b[pivot]);
        T x = T(1)/T(A[rank][col]);
        for(int c = 0; c < m; c++) A[rank][c] *= x;
        b[rank] *= x;
        for(int row = 0; row < n; row++){
            if(row == rank) continue;
            if(is_zero(A[row][col])) continue;
            T x = A[row][col];
            for(int c = 0; c < m; c++) A[row][c] -= A[rank][c]*x;
            b[row] -= b[rank]*x;
        }
        rank++;
    }
    for(int row = rank; row < n; row++){
        if(!is_zero(b[row])) {
            return make_pair(vector<T>(), vector<vector<T>>());
        }
    }
    vector<T> ans(m);
    int idx = 0;
    for(int row = 0; row < rank; row++) {
        while(is_zero(A[row][idx])) idx++;
        ans[idx] = b[row];
    }
    vector<vector<T>> basis;
    for(int col = 0; col < m; col++){
        if(col_pivot[col] != -1) continue;
        vector<T> v(m);
        v[col] = T(1);
        for(int j = 0; j < col; j++){
            if(col_pivot[j] == -1) continue;
            int row = col_pivot[j];
            v[j] = A[row][col]*(-1);
        }
        basis.push_back(v);
    }
    return make_pair(ans, basis);
}
