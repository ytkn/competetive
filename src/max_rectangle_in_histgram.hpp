#include <vector>
#include <stack>

using namespace std;

/**
 * verified: https://atcoder.jp/contests/arc081/submissions/33572531
 */ 
template<typename T>
T max_rectangle_in_histgram(vector<T> h){
    int n = h.size();
    vector<int> l(n), r(n);
    stack<int> st;
    for(int i = 0; i < n; i++){
        while(!st.empty() && h[st.top()] >= h[i]){
            st.pop();
        }
        l[i] = st.empty() ? 0 : st.top()+1;
        st.push(i);
    }
    while(!st.empty()) st.pop();
    for(int i = n-1; i >= 0; i--){
        while(!st.empty() && h[st.top()] >= h[i]){
            st.pop();
        }
        r[i] = st.empty() ? n-1 : st.top()-1;
        st.push(i);
    }
    T ans = 0;
    for(int i = 0; i < n; i++) ans = max(ans, h[i]*(r[i]-l[i]+1));
    return ans;
}