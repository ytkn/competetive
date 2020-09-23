/*
遅延評価セグメント木
単一ノードの更新は区間更新を使って書いて
*/
#include <vector>

using namespace std;

template <typename T, typename S>
struct LazySegmentTree {
    int n;
    T unit;
    vector<T> node;
    vector<S> lazy;
    vector<bool> lazyFlag;

    T calc(T a, T b){
        T ans;
        ans = max(a, b); //適宜変える
        return ans;
    }

    S calcLazy(S a, S b){
        S ans;
        ans = a+b; //適宜変える
        return ans;
    }

    S propagateLazy(S lazy1, S lazy2){
        return lazy1+lazy2; //適宜変える
    }

    T merge(T node, S lazy){
        return node+lazy; //適宜変える
    }

    S clearLazy(){
        return 0; //適宜変える
    }

    LazySegmentTree(vector<T> v, T UNIT, S UNIT_LAZY) {
        int sz = (int)v.size();
        unit = UNIT;
        n = 1; while(n < sz) n *= 2;
        node.resize(2*n-1, unit);
        lazy.resize(2*n-1, UNIT_LAZY);
        lazyFlag.resize(2*n-1, false);

        for(int i=0; i<sz; i++) node[i+n-1] = v[i];
        for(int i=n-2; i>=0; i--) node[i] = calc(node[i*2+1], node[i*2+2]);
    }

    void lazyEvaluate(int k, int l, int r) {
        if(lazyFlag[k]) {
            node[k] = merge(node[k], lazy[k]);
            if(r - l > 1) {
                lazy[k*2+1] = propagateLazy(lazy[k*2+1], lazy[k]);
                lazy[k*2+2] = propagateLazy(lazy[k*2+2], lazy[k]);
                lazyFlag[k*2+1] = lazyFlag[k*2+2] = true;
            }
            lazyFlag[k] = false;
            lazy[k] = clearLazy();
        }
    }

    //[a, b)
    //区間[a, b]への更新に対してはupdate(a, b+1, x)と呼ぶ
    void update(int a, int b, S x, int k=0, int l=0, int r=-1) {
        if(r < 0) r = n;
        lazyEvaluate(k, l, r);
        if(b <= l || r <= a) return;
        if(a <= l && r <= b) {
            lazy[k] = calcLazy(lazy[k], x);
            lazyFlag[k] = true;
            lazyEvaluate(k, l, r);
        }
        else {
            update(a, b, x, 2*k+1, l, (l+r)/2);
            update(a, b, x, 2*k+2, (l+r)/2, r);
            node[k] = calc(node[2*k+1], node[2*k+2]);
        }
    }

    //[a, b)
    //区間[a, b]へのクエリに対してはquery(a, b+1)と呼ぶ
    T query(int a, int b, int k=0, int l=0, int r=-1) {
        if(r < 0) r = n;
        lazyEvaluate(k, l, r);
        if(b <= l || r <= a) return unit;
        if(a <= l && r <= b) return node[k];
        T vl = query(a, b, 2*k+1, l, (l+r)/2);
        T vr = query(a, b, 2*k+2, (l+r)/2, r);
        return calc(vl, vr);
    }
};