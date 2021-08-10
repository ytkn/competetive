#include <vector>
#include <cassert>
#include <iostream>

using namespace std;


inline int kth_bit(int x, int k){
    return x&(1<<k) ? 1 : 0;
}

/**
 * 色々と不完全だしdepthが逆だしであれだけど一応取っておく。
 * 直してくれ。
 */ 
struct Tree{
    struct node{
        int val, cnt, depth;
        vector<int> children;
        node(int val, int cnt, int depth): val(val), cnt(cnt), depth(depth) {
            children = vector<int>();
        };
    };

    vector<node> nodes;
    int n_nodes = 0;
    int n_bits;
    Tree(int n_bits): n_bits(n_bits) {
        nodes.push_back(node(0, 0, n_bits));
        n_nodes = 1;
    };

    int get_child(int nd_idx, int x){
        for(int i: nodes[nd_idx].children){
            if(nodes[i].val == x) return i;
        }
        assert(false);
    }

    int root(){
        return 0;
    }

    bool has_child(int nd_idx, int x, bool require_pos = false){
        for(int i: nodes[nd_idx].children){
            if(require_pos){
                if(nodes[i].val == x && nodes[i].cnt > 0) return true;
            }else{
                if(nodes[i].val == x) return true; 
            }
        }
        return false;
    }

    void add(int nd_idx, int x){
        nodes[nd_idx].cnt++;
        if(nodes[nd_idx].depth == 0) return;
        int v = kth_bit(x, nodes[nd_idx].depth-1);
        if(!has_child(nd_idx, v)){
            nodes.push_back(node(v, 0, nodes[nd_idx].depth-1));
            nodes[nd_idx].children.push_back(n_nodes);
            n_nodes++;
        }
        add(get_child(nd_idx, v), x);
    }

    void add(int x){
        add(root(), x);
    }

    void erase(int nd_idx, int x){
        nodes[nd_idx].cnt--;
        if(nodes[nd_idx].depth == 0) return;
        int v = kth_bit(x, nodes[nd_idx].depth-1);
        erase(get_child(nd_idx, v), x);
    }

    void erase(int x){
        erase(root(), x);
    }

    void dfs(node &nd){
        cout << nd.depth << ' ' << nd.val << ' ' << nd.cnt << endl;
        for(int i: nd.children) dfs(nodes[i]);
    }

    void dfs(){
        dfs(nodes[0]);
    }
};
