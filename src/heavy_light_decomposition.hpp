#include <vector>
#include <cassert>

using namespace std;

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }

using P = pair<int, int>;

/**
 * verified?: https://atcoder.jp/contests/kupc2021/submissions/27139986
 */ 
class HeavyLightDecomposition{
    public:
    int n;
    vector<vector<int>> tree;
    vector<int> parents; // もとの木におけるindex
    vector<vector<int>> components;
    vector<P> pos; // (component_idx, ord in component)
    int root;
    HeavyLightDecomposition(vector<vector<int>> tree, int root): tree(tree), root(root){
        n = tree.size();
        pos.resize(n);
        seen.resize(n);
        subtree_size.resize(n);
        exec();
    }
    private:
    vector<bool> seen;
    vector<int> subtree_size;
    void exec(){
        vector<int> nx(n, -1);
        dfs1(root, nx);
        seen.assign(n, false);
        int m = 0;
        parents.push_back(-1);
        dfs2(root, nx, 0);
    }
    void add_to_component(int v, int component_idx){
        assert(component_idx <= components.size());
        if(components.size() == component_idx){
            components.push_back({});
        }
        pos[v] = P(component_idx, components[component_idx].size());
        components[component_idx].push_back(v);
    }
    void dfs1(int v, vector<int> &nx){
        seen[v] = true;
        subtree_size[v] = 1;
        int max_size = -1;
        for(int to: tree[v]){
            if(seen[to]) continue;
            dfs1(to, nx);
            subtree_size[v] += subtree_size[to];
            if(chmax(max_size, subtree_size[to])) nx[v] = to;
        }
    }

    void dfs2(int v, vector<int> &nx, int component_idx){
        seen[v] = true;
        add_to_component(v, component_idx);
        for(int to: tree[v]){
            if(seen[to]) continue;
            if(to == nx[v]){
                dfs2(to, nx, component_idx);
            }else{
                parents.push_back(v);
                dfs2(to, nx, components.size());
            }
        }
    }
};