#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
typedef long long ll;

/**
 * verified?: https://atcoder.jp/contests/tenka1-2016-final/submissions/24942772
 */ 
class Trie{
    struct node{
        char val;
        int depth;
        bool is_end;
        vector<int> children;
        node(char val, int depth): val(val), depth(depth) {
            children = vector<int>();
            is_end = false;
        };
    };
    public:
    vector<node> nodes;
    int n_nodes = 0;
    int n_bits;
    Trie() {
        nodes.push_back(node('#', 0));
        n_nodes = 1;
    };

    int get_child(int nd_idx, char c){
        for(int i: nodes[nd_idx].children){
            if(nodes[i].val == c) return i;
        }
        assert(false);
    }

    int root(){
        return 0;
    }

    bool has_child(int nd_idx, char c){
        for(int i: nodes[nd_idx].children){
            if(nodes[i].val == c) return true;
        }
        return false;
    }

    void add(string &s, int score){
        add(root(), s, score);
    }

    void dfs(){
        for(int i: nodes[root()].children) dfs(nodes[i], "");
    }

    private:
    void add(int nd_idx, string &s, int score){
        int depth = nodes[nd_idx].depth;
        if(depth == s.size()) {
            nodes[nd_idx].is_end = true;
            return;
        }
        if(!has_child(nd_idx, s[depth])){
            nodes.push_back(node(s[depth], depth+1));
            nodes[nd_idx].children.push_back(n_nodes);
            n_nodes++;
        }
        add(get_child(nd_idx, s[depth]), s, score);
    }

    void dfs(node &nd, string s){
        s += nd.val;
        if(nd.is_end){
            cout << s << endl;
        }
        for(int i: nd.children) dfs(nodes[i], s);
    }
};