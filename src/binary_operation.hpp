#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;

/**
 * vを二進数とみなして1を加えて返します(v[0]が0-bit目と扱われる事に注意)
 * ex) add_one({0, 1, 1, 1}) -> {1, 1, 1, 1}
 */ 
vector<int> add_one(vector<int> v){
    vector<int> u;
    int carry = 1;
    for(int x: v){
        if(x == 1 && carry == 1){
            u.push_back(0);
        }else{
            u.push_back(x+carry);
            carry = 0;
        }
    }
    if(carry == 1) u.push_back(1);
    return u;
}

/**
 * sを二進数とみなして1を加えて返します(末尾が0-bit目と扱われる事に注意)
 * ex) add_one("1110") -> "1111"
 */ 
string add_one(string s){
    int n = s.size();
    vector<int> v;
    for(char c: s) v.push_back(c-'0');
    reverse(v.begin(), v.end());
    vector<int> u;
    int carry = 1;
    for(int x: v){
        if(x == 1 && carry == 1){
            u.push_back(0);
        }else{
            u.push_back(x+carry);
            carry = 0;
        }
    }
    if(carry == 1) u.push_back(1);
    reverse(u.begin(), u.end());
    string t;
    for(int x: u) t += '0'+x;
    return t;
}
