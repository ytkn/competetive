#include <array>
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

inline int kth_bit(long long x, int k){
    return (x&(1ll<<k)) ? 1 : 0;
}

inline int kth_bit(int x, int k){
    return (x&(1<<k)) ? 1 : 0;
}

/**
 * verified: https://judge.yosupo.jp/submission/73930
 */ 
template<typename T, int MAX_BIT=30>
struct BinaryTrie{
    struct node{
        int cnt, bit_idx;
        array<int, 2> children;
        node(int cnt, int bit_idx): cnt(cnt), bit_idx(bit_idx) {
            children[0] = -1;
            children[1] = -1;
        };
    };

    public:
    vector<node> nodes;
    int n_nodes = 0;
    BinaryTrie() {
        nodes.push_back(node(0, MAX_BIT));
        n_nodes = 1;
    };

    BinaryTrie(vector<int> v) {
        nodes.push_back(node(0, MAX_BIT));
        n_nodes = 1;
        for(int x: v) add(x);
    };

    int root(){
        return 0;
    }

    void add(T x){
        add(root(), x);
    }

    /**
     * xを消して、もともと何個あったかを返します
     */ 
    int erase(T x){
        return erase(root(), x);
    }

    T max_xor(T x){
        assert(nodes[root()].cnt > 0);
        return max_xor(nodes[root()], x);
    }

    T min_xor(T x){
        assert(nodes[root()].cnt > 0);
        return min_xor(nodes[root()], x);
    }

    private:
    int erase(const int idx, T x){
        if(nodes[idx].cnt == 0) return 0;
        if(nodes[idx].bit_idx == 0) {
            int ret = nodes[idx].cnt;
            nodes[idx].cnt = 0;
            return ret;
        }
        int v = kth_bit(x, nodes[idx].bit_idx-1);
        if(nodes[idx].children[v] == -1) return 0;
        int ret = erase(nodes[idx].children[v], x);
        nodes[idx].cnt -= ret;
        return ret;
    }

    void add(const int idx, T x){
        nodes[idx].cnt++;
        if(nodes[idx].bit_idx == 0) return;
        int v = kth_bit(x, nodes[idx].bit_idx-1);
        if(nodes[idx].children[v] == -1){
            nodes.push_back(node(0, nodes[idx].bit_idx-1));
            nodes[idx].children[v] = n_nodes;
            n_nodes++;
        }
        assert(nodes[idx].children[v] != -1);
        add(nodes[idx].children[v], x);
    }

    T max_xor(const node &nd, T x){
        assert(nd.cnt > 0);
        if(nd.bit_idx == 0) return T(0);
        int v = kth_bit(x, nd.bit_idx-1);
        if(nd.children[v^1] != -1 && nodes[nd.children[v^1]].cnt > 0){
            return max_xor(nodes[nd.children[v^1]], x) + (T(1) << (nd.bit_idx-1));
        }else{
            return max_xor(nodes[nd.children[v]], x);
        }
    }

    T min_xor(const node &nd, T x){
        assert(nd.cnt > 0);
        if(nd.bit_idx == 0) return T(0);
        int v = kth_bit(x, nd.bit_idx-1);
        if(nd.children[v] != -1 && nodes[nd.children[v]].cnt > 0){
            return min_xor(nodes[nd.children[v]], x);
        }else{
            return min_xor(nodes[nd.children[v^1]], x) + (T(1) << (nd.bit_idx-1));
        }
    }

};