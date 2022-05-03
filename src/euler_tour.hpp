#include <vector>
#include <cassert>

using namespace std;

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }


/**
 * 変数の意味は概ね[maspyさんの記事](https://maspypy.com/euler-tour-%E3%81%AE%E3%81%8A%E5%8B%89%E5%BC%B7#toc1)に準じています(ありがとうございます)
 */ 
class EulerTour{
    public:
    vector<vector<int>> g;
    int root;
    int n;
    vector<int> depth;
    vector<int> ord;
    vector<int> in, out;
    EulerTour(vector<vector<int>> g, int root): g(g), root(root){
        n = g.size();
        depth.resize(n);
        in.resize(n);
        out.resize(n);
        build();
    }
    private:
    void build(){
        vector<bool> seen(n, false);
        dfs(root, seen);
        for(int i = 0; i < n; i++) in[i] = 1e9;
        for(int i = 0; i < ord.size(); i++){
            chmin(in[ord[i]], i);
            chmax(out[ord[i]], i);
        }
        assert(ord.size() == 2*n);
    }
    void dfs(int v, vector<bool> &seen){
        ord.push_back(v);
        seen[v] = true;
        int cnt = 0;
        for(int to: g[v]){
            if(seen[to]) continue;
            depth[to] = depth[v]+1;
            dfs(to, seen);
            cnt++;
        }
        ord.push_back(v);
    }
};
