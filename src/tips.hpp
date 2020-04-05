#include <iostream>

using namespace std;

typedef long long ll;
const ll MOD = 1000000007;

template <typename T>
T pow_int(T a, ll n){
    T ans = 1;
    T tmp = a;
    for(int i = 0; i <= 60; i++){
        ll m = (ll)1 << i;
        if(m&n){
            ans *= tmp;
            ans %= MOD;
        }
        tmp *= tmp;
        tmp %= MOD;
    }
    return ans;
}

// nを超えない最大のmの倍数をもとめる
int calc_nmul(int n, int m){
    return (n/m)*m;
}