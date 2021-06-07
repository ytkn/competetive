#include <vector>
#include <bitset>
#include <cassert>

using namespace std;

const int MAX_COL = 305;

class BitMatrix{
    public:
    int h;
    int w;
    vector<bitset<MAX_COL>> val;

    BitMatrix(int h, int w): h(h), w(w){
        val.resize(h);
        assert(w <= MAX_COL);
    };

    BitMatrix(int h, int w, vector<bitset<MAX_COL>> val): h(h), w(w), val(val){
        assert(h == val.size());
        assert(w <= MAX_COL);
    };

    inline bitset<MAX_COL>& operator [] (int i) { return val[i];}
};

/**
 * Ax = bを解きます。Aは横ベクトルのvectorを与えること
 * return: (x, rank)
 * rank = -1の場合は解なし
 */ 
pair<vector<int>, int> solve_f2_linear_equation(BitMatrix A, vector<int> b){
    assert(A.h == b.size());
    int rank = 0;
    // 掃き出し
    for(int j = 0; j < A.w; j++){
        int pivot = [&](){
            for(int i = rank; i < A.h; i++) if(A[i][j]) return i;
            return -1;
        }();
        if(pivot == -1) continue;
        swap(A[rank], A[pivot]);
        swap(b[rank], b[pivot]);
        for(int i = 0; i < A.h; i++){
            if(i == rank) continue;
            if(A[i][j]) {
                A[i] ^= A[rank];
                b[i] ^= b[rank];
            }
        }
        rank++;
    }
    for(int i = rank; i < A.h; i++) {
        if(b[i]) return make_pair(vector<int>(), -1);
    }
    vector<int> x(A.w);
    for(int i = 0; i < rank; i++) x[i] = b[i];
    return make_pair(x, rank);
}