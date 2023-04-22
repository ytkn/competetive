#include <vector>

using namespace std;

template<typename T>
vector<int> manacher(vector<T> s){
    int n = s.size();
    int i = 0, j = 0;
    vector<int> r(n);
    while(i < s.size()){
        while(i >= j && i+j < s.size() && s[i-j] == s[i+j]){
            j++;
        }
        r[i] = j;
        int k = 1;
        while(i >= k && i+k < s.size() && k+r[i-k] < j){
            r[i+k] = r[i-k];
            k++;
        }
        i += k;
        j -= k;
    }
    return r;
}