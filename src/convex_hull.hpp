#include <vector>
#include "coord.hpp"

using namespace std;

template<typename T>
bool comp_p(point<T> p, point<T> q){
    if(p.x != q.x) return p.x < q.x;
    return p.y < q.y;
}

template<typename T>
vector<point<T>> convex_hull(vector<point<T>> ps){
    int n = ps.size();
    sort(ps.begin(), ps.end(), comp_p<T>);
    vector<point<T>> ans;
    for(int i = 0; i < n; i++){
        while(ans.size() > 1 && (ans[ans.size()-1]-ans[ans.size()-2]).det(ps[i] - ans[ans.size()-1]) <= 0) ans.pop_back();
        ans.push_back(ps[i]);
    }
    int bottom_size = ans.size();
    for(int i = n-2; i >= 0; i--){
        while(ans.size() > bottom_size && (ans.back()-ans[ans.size()-2]).det(ps[i] - ans.back()) <= 0) ans.pop_back();
        ans.push_back(ps[i]);
    }
    ans.pop_back();
    return ans;
}