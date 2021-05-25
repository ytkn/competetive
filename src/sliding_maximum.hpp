#include <vector>
#include <deque>

using namespace std;

template <class T>
class SlidingMaximum{
    public:
    deque<T> dq;
    vector<T> a;

    void push_right(int r, T x){
        assert(r == a.size());
        a.push_back(x);
        while(!dq.empty() && a[dq.back()] <= x) dq.pop_back();
        dq.push_back(r);
    }

    /**
     * NOTE: indexがl以下のものを削除することに注意
     */ 
    void pop_left(int l){
        while(!dq.empty() && dq.front() <= l) dq.pop_front();
    }

    T query(){ 
        return a[dq.front()];
    }
};