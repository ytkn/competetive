#include <vector>

using namespace std;
typedef long long ll;

template <typename T>
T gcd(T a, T b){
    if(a < b) swap(a, b);
    while(b != 0){
        T tmp = b;
        b = a%b;
        a = tmp;
    }
    return a;
}

template <typename T>
T lcm(T a, T b){
    return (a*b)/gcd<T>(a, b);
}

template <typename T>
T pow(T a, ll n){
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

template <typename T>
vector<T> divs(T N){
    vector<T> ans;
    for(int i = 1; i*i <= N; i++){
        if(N%i == 0){
            ans.push_back(i);
            if(i*i != N) ans.push_back(N/i);
        }
    }
    return ans;
}

template <typename T>
vector<T> prime_facs(T N){
    vector<T> ans;
    for(int i = 2; i*i <= N; i++){
        if(N%i == 0){
            ans.push_back(i);
            while(N%i == 0){
                N /= i;
            }
        }
    }
    if(N != 1) ans.push_back(N);
    return ans;
}

template <typename T>
vector<T> divs(T N){
    vector<T> ans;
    for(int i = 1; i*i <= N; i++){
        if(N%i == 0){
            ans.push_back(i);
            if(i*i != N) ans.push_back(N/i);
        }
    }
    return ans;
}