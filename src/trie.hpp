#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

struct node{
    char val;
    ll w = 0;
    int depth;
    vector<node> next;
};

node* getNode(node &cur, char c){
    for(int i = 0; i < cur.next.size(); i++){
        if(cur.next[i].val == c) return &(cur.next[i]);
    }
}

bool hasChar(node &cur, char c){
    for(int i = 0; i < cur.next.size(); i++){
        if(cur.next[i].val == c) return true;
    }
    return false;
}

void addNode(node &cur, char c, ll w){
    node n;
    n.depth = cur.depth+1;
    n.val = c;
    if(w == 0) n.w = 0;
    else n.w = max(w, n.w);
    cur.next.push_back(n);
}