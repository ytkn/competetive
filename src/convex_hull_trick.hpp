#include <vector>
#include <deque>
#include <cassert>

using namespace std;

/**
 * verified: https://atcoder.jp/contests/abc228/submissions/27464591
 */ 
template<typename T>
class ConvexHullTrick{
    public:
    T x;
    ConvexHullTrick<T>(){
        x = 0;
    }
    /**
     * xを一つ進めます
     */ 
    void next(){
        x++;
        while(dq.size() >= 2 && f(x, dq[0]) >= f(x, dq[1])) dq.pop_front();
    }
    /**
     * xを指定された値まで進めます
     */ 
    void proceed(T _x){
        assert(x <= _x);
        x = _x;
        while(dq.size() >= 2 && f(x, dq[0]) >= f(x, dq[1])) dq.pop_front();
    }
    /**
     * 直線 y = p_add*x+q を追加します(今まで追加した中で傾きが最小の直線であること)
     */ 
    void add_line(T p_add, T q_add){
        if(!dq.empty()) assert(p_add < p[dq.back()]);
        p.push_back(p_add);
        q.push_back(q_add);
        int n_lines = p.size();
        while(dq.size() >= 2 && check(dq[dq.size()-2], dq.back(), n_lines-1)) {
            dq.pop_back();
        }
        dq.push_back(n_lines-1);
    }
    T get_min(){
        return f(x, dq[0]);
    }
    private:
    vector<T> p, q; // 直線p[i]x+q[i]
    deque<int> dq;
    T f(int x, int i){
        return p[i]*x+q[i];
    }
    bool check(int i, int j, int k){
        return (p[j]-p[i])*(q[k]-q[j]) >= (q[j]-q[i])*(p[k]-p[j]);
    };
};
