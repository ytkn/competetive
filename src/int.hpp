#include <vector>
#include <initializer_list>

#define MOD 1000000007

using namespace std;
typedef long long ll;


template <typename T>
T gcd(initializer_list<T> v) {
	T ans = 0;
    for(T x : v) ans = gcd(ans, x);
	return ans;
}

template <typename T>
T gcd(T a, T b) {
	if (a < b) swap(a, b);
		while (b != 0) {
			T tmp = b;
			b = a % b;
			a = tmp;
		}
	return a;
}

template <typename T>
T lcm(T a, T b) {
  	return (a * b) / gcd<T>(a, b);
}

template <typename T>
T pow(T a, ll n) {
	T ans = 1;
	T tmp = a;
	for (int i = 0; i <= 60; i++) {
		ll m = (ll)1 << i;
		if (m & n) {
		ans *= tmp;
		ans %= MOD;
		}
		tmp *= tmp;
		tmp %= MOD;
	}
	return ans;
}

template <typename T>
vector<T> divs(T N) {
	vector<T> ans;
	for (int i = 1; i * i <= N; i++) {
		if (N % i == 0) {
		ans.push_back(i);
		if (i * i != N) ans.push_back(N / i);
		}
	}
	return ans;
}

template <typename T>
vector<T> prime_facs(T N) {
	vector<T> ans;
	for (int i = 2; i * i <= N; i++) {
		if (N % i == 0) {
		ans.push_back(i);
		while (N % i == 0) {
			N /= i;
		}
		}
	}
	if (N != 1) ans.push_back(N);
	return ans;
}

/**
 * i^2+1の形の整数を素因数分解します。
 * ans[i]: i^2+1の素因数分解。
 */ 
template <typename T>
vector<vector<pair<T, int>>> factorize_square_plus_one(ll n){
	vector<ll> v(n+1);
    vector<vector<pair<T, int>>> facs(n+1);
    for(ll i = 1; i <= n; i++) v[i] = i*i+1;
    for(ll i = 1; i <= n; i++){
        if(v[i] != 1){
            ll p = v[i];
            for(ll j = i+p; j <= n; j += p){
                int cnt = 0;
                while(v[j]%p == 0){
                    v[j] /= p;
                    cnt++;
                }
                facs[j].push_back(P(p, cnt));
            }
            if(2*i != p){
                for(ll j = p-i; j <= n; j += p){
                    if(j == i) continue;
                    int cnt = 0;
                    while(v[j]%p == 0){
                        v[j] /= p;
                        cnt++;
                    }
                    facs[j].push_back(P(p, cnt));
                }
            }
        }
    }
    for(int i = 1; i <= n; i++){
        if(v[i] != 1) facs[i].push_back(P(v[i], 1));
    }
	return facs;
}