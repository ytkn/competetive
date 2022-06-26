#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

/**
 * verified: https://codeforces.com/contest/1195/submission/161851257
 */ 
template<typename T>
class Mo{
    public:
    vector<int> l, r;
    int bucket_size;
    Mo(int bucket_size): l(vector<int>()), r(vector<int>()), bucket_size(bucket_size) {}
    void add_query(int l_, int r_){
        l.push_back(l_);
        r.push_back(r_);
    }
    template<typename ADD, typename DEL, typename GET_ANS>
    vector<T> solve(ADD add, DEL del, GET_ANS get_ans){
        int sz = l.size();
        vector<int> ord(sz);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](const int a, const int b){
            const int c = l[a] / bucket_size, d = l[b] / bucket_size;
            return (c == d) ? ((c & 1) ? (r[b] < r[a]) : (r[a] < r[b])) : (c < d);
        });
        int li = 0, ri = 0;
        vector<T> ans(sz);
        for(const int i : ord){
            while(li > l[i]) add(--li);
            while(ri < r[i]) add(ri++);
            while(li < l[i]) del(li++);
            while(ri > r[i]) del(--ri);
            ans[i] = get_ans();
        }
        return ans;
    }
};