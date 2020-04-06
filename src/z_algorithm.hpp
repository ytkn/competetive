#include <iostream>
#include <vector>

using namespace std;

vector<int> z_algorithm(string s){
    int n = s.size();
    vector<int> ans(n);
    ans[0] = n;
    int i = 1, j = 0;
    while(i < s.size()){
        while(i+j < s.size() && s[i+j] == s[j]) j++;
        if(j == 0) {
            i++;
            continue;
        }
        ans[i] = j;
        int k = 1;
        while(k < j && ans[k]+k < j){
            ans[i+k] = ans[k];
            k++;
        }
        i += k;
        j -= k;
    }
    return ans;
}