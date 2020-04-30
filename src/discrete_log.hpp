#include <iostream>
#include <map>
#include <cmath>

using namespace std;

typedef long long ll;

ll inv(ll n, ll p){
    if(n == 1) return 1;
    else return p-inv(p%n, p)*(p/n)%p;
}

/**
 * solve a^x ≡ b (mod p)
 * return -1 when answer does not exist.
 * otherwise return answer 
 */
ll discrete_log(ll a, ll b, ll p){
    ll sq = (ll)sqrt(p)+1;
    map<ll, int> mp;
    ll tmp = 1;
    for(int i = 0; i < sq; i++){
        mp[tmp] = i;
        tmp *= a;
        tmp %= p;
    }
    ll inv_a_pow_sq = inv(tmp, p);
    tmp = b;
    for(int i = 0; i <= sq; i++){
        if(mp.count(tmp) > 0){
            return sq*i+mp[tmp];
        }
        tmp *= inv_a_pow_sq;
        tmp %= p;
    }
    return -1;
}