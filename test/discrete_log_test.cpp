#include "discrete_log.hpp"
#include <vector>

#include "gtest/gtest.h"

template <typename T>
T pow(T a, ll n, ll p) {
	T ans = 1;
	T tmp = a;
	for (int i = 0; i <= 60; i++) {
		ll m = (ll)1 << i;
		if (m & n) {
		ans *= tmp;
		ans %= p;
		}
		tmp *= tmp;
		tmp %= p;
	}
	return ans;
}

void run(ll a, ll b, ll p){
    ll x = discrete_log(a, b, p);
    if(x == -1){
        ll tmp = 1;
        for(int i = 0; i <= p; i++){
            ASSERT_NE(tmp, b);
            tmp *= p;
            tmp %= p;
        }
    }else{
        ll t = pow<ll>(a, x, p);
        ASSERT_EQ(t, b);
    }
}

TEST(discrete_log, calc) {
    run(2, 3, 11);
    run(2, 5, 11);
    run(5, 8, 11);
    run(13, 10, 89);
    run(17, 10, 1000000007);
    run(188, 119, 1000000007);
}
