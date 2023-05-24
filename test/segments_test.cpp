#include <set>
#include "segments.hpp"
#include "generator_utils.cpp"

#include "gtest/gtest.h"


template<typename T>
class NaiveSegments{
    public:
    set<T> st;
    NaiveSegments(): st(set<T>()) {}
    
    /**
     * [l, r)を足す 
     */
    void add(T l, T r){
        for(T x = l; x < r; x++) st.insert(x);
    }

    /**
     * [l, r)を消す
     */
    void remove(T l, T r){
        for(T x = l; x < r; x++) st.erase(x);
    }

    /**
     * [l, r)と被る区間
     */
    vector<pair<T, T>> overlaps(T l, T r){
        set<T> ans;
        for(T x = l; x < r; x++) {
            if(st.count(x)) ans.insert(x);
        }
        return concat_segments(ans);
    }

    /**
     * [l, r)と被らない区間
     */
    vector<pair<T, T>> not_covered(T l, T r){
        set<T> ans;
        for(T x = l; x < r; x++) {
            if(st.count(x) == 0) ans.insert(x);
        }
        return concat_segments(ans);
    }

    vector<pair<T, T>> concat_segments(set<T> target){
        bool seen = false;
        T start = -1;
        T last = -1;
        vector<pair<T, T>> ans;
        for(T x: target){
            if(!seen){
                seen = true;
                start = x;
                last = x;
                continue;
            }
            if(last+1 == x){
                last = x;
            }else{
                ans.push_back({start, last+1});
                start = x;
                last = x;
            }
        }
        if(seen){
            ans.push_back({start, last+1});
        }
        return ans;
    }

    vector<pair<T, T>> get_segments(){
        return concat_segments(st);
    }

    void debug(){
        for(auto [l, r]: get_segments()){
            cerr << "[" << l << ',' << r << "] ";
        }
        cerr << endl;
    }
};

void random_test(int max_len, int iter){
    auto seg = Segments<int>();
    auto naive = NaiveSegments<int>();
    while(iter--){
        int t = randint(0, 4);
        int l = randint(0, 100);
        int r = l+randint(0, max_len);
        if(l > r) swap(l, r);
        if(t == 0){ // add
            seg.add(l, r);
            naive.add(l, r);
        }else if(t == 1){ // remove
            seg.remove(l, r);
            naive.remove(l, r);
        }else if(t == 2){ // overlap
            ASSERT_EQ(seg.overlaps(l, r), naive.overlaps(l, r));
        }else{ // not covered
            ASSERT_EQ(seg.not_covered(l, r), naive.not_covered(l, r));
        }
        
        auto segments_by_naive = naive.get_segments();
        ASSERT_EQ(segments_by_naive.size(), seg.mp.size());
        for(auto [l, r]: naive.get_segments()){
            ASSERT_EQ(seg.mp[l], r);
        }
    }
}

TEST(segments, random) {
    for(int i = 0; i < 50; i++){
        int max_len = [&](){
            if(i%3 == 0) return 5;
            if(i%3 == 1) return 10;
            if(i%3 == 2) return 50;
        }();
        random_test(max_len, 1000);
    }
}
