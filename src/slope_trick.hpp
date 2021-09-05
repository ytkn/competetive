#include <vector>
#include <queue>

using namespace std;

/**
 * https://atcoder.jp/contests/abc217/submissions/25632592
 */ 
template<typename T>
class SlopeTrick {
    public:
    SlopeTrick() {
        min_f = 0;
        add_l = 0;
        add_r = 0;
    }

    void add_pos(T a){ // add max(x-a, 0)
        l.push(a-add_l);
        T l0 = l.top()+add_l; l.pop();
        r.push(l0-add_r);
        min_f += max<T>(l0-a, 0);
    }

    void add_neg(T a){ // add max(a-x, 0)
        r.push(a-add_r);
        T r0 = r.top()+add_r; r.pop();
        l.push(r0-add_l);
        min_f += max<T>(a-r0, 0);
    }

    void slide_neg(T a){
        add_l += a;
    }

    void slide_pos(T a){
        add_r += a;
    }

    T get_min(){
        return min_f;
    }

    /**
     * be careful that this method takes O(NlonN) time (N := r.size()+l.size()).
     */ 
    T eval(T x) {
        T ans = min_f;
        vector<T> buf;
        while(!l.empty()){
            buf.push_back(l.top());
            l.pop();
        }
        for(T a: buf){
            l.push(a);
            ans += max<T>(a+add_l-x, 0);
        }
        buf.clear();
        while(!r.empty()){
            buf.push_back(r.top());
            r.pop();
        }
        for(T a: buf){
            r.push(a);
            ans += max<T>(x-a-add_r, 0);
        }
        return ans;
    }

    private:
    priority_queue<T> l;
    priority_queue<T, vector<T>, greater<T>> r;
    T min_f;
    T add_l;
    T add_r;
};
