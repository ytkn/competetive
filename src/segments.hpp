#include <vector>
#include <map>
#include <cassert>
#include <iostream>

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

using namespace std;

template<typename T>
class Segments{
    public:
    map<T, T> mp;
    Segments(): mp(map<T, T>()) {}
    
    /**
     * [l, r)を足す 
     */
    void add(T l, T r){
        assert(l <= r);
        if(l == r) return;
        auto pl = mp.lower_bound(l);
        if(pl != mp.begin()){
            auto [l_prev, r_prev] = *prev(pl);
            if(r_prev >= l){
                pl--;
            }
        }
        auto pr = pl;
        while(pr != mp.end()){
            auto [l0, r0] = *pr;
            if(l0 <= r){
                chmin(l, l0);
                chmax(r, r0);
            }else{
                break;
            }
            pr++;
        }
        mp.erase(pl, pr);
        mp[l] = r;
    }

    /**
     * [l, r)を消す
     */
    void remove(T l, T r){
        assert(l <= r);
        if(l == r) return;
        auto pl = mp.lower_bound(l);
        auto pr = pl;
        // 完全に被る区間
        while(pr != mp.end()){
            auto [l0, r0] = *pr;
            if(pr->second > r) break;
            pr++;
        }
        mp.erase(pl, pr);
        auto p = mp.lower_bound(l);
        if(p != mp.begin()){
            if(prev(p)->second > r){
                auto [l0, r0] = *prev(p);
                chmin(prev(p)->second, l);
                mp[r] = r0;
                return;
            }else{
                chmin(prev(p)->second, l);
            }
        }
        if(p != mp.end()){
            auto [l0, r0] = *p;
            if(l0 < r){
                mp.erase(p);
                mp[r] = r0;
            }
        }
    }

    /**
     * [l, r)と被る区間
     */
    vector<pair<T, T>> overlaps(T l, T r){
        assert(l <= r);
        if(l == r) return {};
        auto p = mp.lower_bound(l);
        vector<pair<T, T>> ans;
        auto add = [&](T l0, T r0){
            ans.push_back({max(l0, l), min(r0, r)});
        };
        if(p != mp.begin()){
            auto [l_prev, r_prev] = *prev(p);
            if(r_prev > l){
                add(l_prev, r_prev);
            }
        }
        while(p != mp.end()){
            auto [l0, r0] = *p;
            if(l0 < r){
                add(l0, r0);
            }else{
                break;
            }
            p++;
        }
        return ans;
    }

    /**
     * [l, r)と被らない区間
     */
    vector<pair<T, T>> not_covered(T l, T r){
        assert(l <= r);
        if(l == r) return {};
        auto p = mp.lower_bound(l);
        vector<pair<T, T>> ans;
        auto add = [&](T l0, T r0){
            ans.push_back({max(l0, l), min(r0, r)});
        };
        T tail = l;
        if(p != mp.begin()){
            auto [l_prev, r_prev] = *prev(p);
            if(r_prev > l){
                tail = r_prev;
            }
        }
        while(p != mp.end()){
            auto [l0, r0] = *p;
            if(l0 < r){
                if(tail < l0) ans.push_back({tail, l0});
                tail = r0;
            }else{
                break;
            }
            p++;
        }
        if(tail < r){
            ans.push_back({tail, r});
        }
        return ans;
    }

    void debug(){
        for(auto [l, r]: mp) cerr << "[" << l << ',' << r << "] ";
        cerr << endl;
    }
};
