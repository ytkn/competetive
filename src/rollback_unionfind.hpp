#include <vector>
#include <stack>

using namespace std;

/**
 * verified: https://judge.yosupo.jp/submission/86411
 */ 
struct RollbackUnionFind{
    int n;
    vector<int> data;
    stack<pair<pair<int, int>, pair<int, int>>> history;
    RollbackUnionFind(int n): n(n), data(n, -1) {}
    bool unionSet(int x, int y) {
        x = root(x); y = root(y);
        history.push(make_pair(make_pair(x, data[x]), make_pair(y, data[y])));
        if (x != y) {
        if (data[y] < data[x]) swap(x, y);
        data[x] += data[y]; data[y] = x;
        }
        return x != y;
    }
    bool findSet(int x, int y) {
        return root(x) == root(y);
    }
    int root(int x) {
        return data[x] < 0 ? x : root(data[x]);
    }
    int size(int x) {
        return -data[root(x)];
    }
    void undo(){
        auto p1 = history.top().first;
        auto p2 = history.top().second;
        history.pop();
        data[p1.first] = p1.second;
        data[p2.first] = p2.second;
    }
};
