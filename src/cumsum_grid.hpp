#include <vector>

using namespace std;

template<typename T>
class CumsumGrid{
    public:
    CumsumGrid(vector<vector<T>> v): v(v){
        n = v.size();
        m = v[0].size();
        v_cumsum = vector<vector<T>>(n+1, vector<T>(m+1, T(0)));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++){
                v_cumsum[i+1][j+1] = v_cumsum[i+1][j]+v_cumsum[i][j+1]-v_cumsum[i][j]+v[i][j];
            }
        }
    }
    /**
     * sum(v[il:ir)[jl:jr))
     */ 
    T sum(int il, int ir, int jl, int jr){
        if(ir <= il) return T(0);
        if(jr <= jl) return T(0);
        if(ir > n) ir = n;
        if(jr > m) jr = m;
        if(il < 0) il = 0;
        if(jl < 0) jl = 0;
        return v_cumsum[ir][jr]-v_cumsum[ir][jl]-v_cumsum[il][jr]+v_cumsum[il][jl];
    }
    private:
    int n, m;
    vector<vector<T>> v;
    vector<vector<T>> v_cumsum;
};
