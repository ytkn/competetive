#include <vector>

using namespace std;

/**
 * 変数の意味は概ね[maspyさんの記事](https://maspypy.com/euler-tour-%E3%81%AE%E3%81%8A%E5%8B%89%E5%BC%B7#toc1)に準じています(ありがとうございます)
 */ 
class EulerTour{
    public:
    vector<vector<int>> g;
    int root;
    int n;
    vector<int> ord;
    vector<int> in, out;
    EulerTour(vector<vector<int>> g, int root): g(g), root(root){
        n = g.size();
        in.resize(n);
        out.resize(n);
        build();
    }
    private:
    void build(){
        vector<bool> seen(n, false);
        dfs(0, seen);
    }
    void dfs(int v, vector<bool> &seen){
        seen[v] = true;
        in[v] = ord.size();
        ord.push_back(v);
        int cnt = 0;
        for(int to: g[v]){
            if(seen[to]) continue;
            dfs(to, seen);
            cnt++;
        }
        if(cnt > 0) {
            out[v] = ord.size();
            ord.push_back(v);
        }else{
            out[v] = ord.size()-1;
        }
    }
};
