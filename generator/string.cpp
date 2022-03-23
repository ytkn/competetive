#include <iostream>
#include "generator/generator_utils.cpp"

using namespace std;

string gen_str(int len, int n_chars){
    string ans;
    for(int i = 0; i < len; i++){
        ans += randint(0, n_chars)+'a';
    }
    return ans;
}