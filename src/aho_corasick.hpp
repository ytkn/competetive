#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

/**
 * verified?: https://yukicoder.me/submissions/729519, https://yukicoder.me/problems/no/1269/submissions
 */
class AhoCorasick {
    struct Edge{
        int to;
        char c;
        Edge(int to, char c): to(to), c(c) { }
    };
    public:
    vector<string> key_words;
    int n_nodes;
    AhoCorasick(vector<string> key_words): key_words(key_words) {
        n_nodes = 1;
        output = {{}};
        tree = {{}};
        for(int i = 0; i < key_words.size(); i++) {
            add(i);
        }
        // build failure and output
        failure.resize(n_nodes);
        failure[0] = 0;
        queue<int> que;
        for(Edge e: tree[0]){
            que.push(e.to);
            failure[e.to] = 0;
        }
        while(!que.empty()){
            int v = que.front(); que.pop();
            for(Edge e: tree[v]){
                que.push(e.to);
                int u = failure[v];
                while(find_node(u, e.c) == -1 && u != 0) {
                    u = failure[u];
                }
                failure[e.to] = find_node(u, e.c);
                if(u == 0 && failure[e.to] == -1){
                    failure[e.to] = 0;
                }
                for(int i: output[failure[e.to]]) output[e.to].insert(i);
            }
        }
    }
    vector<int> search_text(string text){
        int cur = 0;
        vector<int> ans(key_words.size());
        for(char c: text){
            while(true){
                int nx = find_node(cur, c);
                if(cur == 0 && nx == -1){
                    nx = 0;
                }
                if(nx != -1) {
                    cur = nx;
                    break;
                }
                cur = failure[cur];
            }
            for(int i: output[cur]) ans[i]++;
        }
        return ans;
    }       
    private:
    vector<vector<Edge>> tree;
    vector<int> failure;
    vector<set<int>> output;
    void add(int idx){
        int cur = 0;
        for(char c: key_words[idx]){
            int nx = find_node(cur, c);
            if(nx == -1){
                nx = add_node(cur, c);
            }
            cur = nx;
        }
        output[cur].insert(idx);
    }
    
    int find_node(int i, char c){
        for(Edge e: tree[i]){
            if(e.c == c) return e.to;
        }
        return -1;
    }
    int add_node(int from, char c){
        int to = n_nodes;
        tree[from].push_back(Edge(to, c));
        n_nodes++;
        output.push_back({});
        tree.push_back({});
        return to;
    }
};
