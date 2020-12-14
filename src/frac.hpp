#include <iostream>
#include "int.hpp"

using namespace std;

/**
 * 有理数の計算用
 * atcoderだとたいていmodintで足りるが、Project Eulerだとたまに使える。
 */ 
template <typename T>
class frac{
    public:
    T n, d;
    frac(T _n, T _d){
        T g = gcd(_n, _d);
        n = _n/g;
        d = _d/g;
    }
    frac operator+(frac f){
        return frac(n*f.d+d*f.n, f.d*d);
    }
    frac operator-(frac f){
        return frac(n*f.d-d*f.n, f.d*d);
    }
    void operator+=(frac f){
        n = n*f.d+d*f.n, d = f.d*d;
        reduction();
    }
    void operator-=(frac f){
        n = n*f.d-d*f.n, d = f.d*d;
        reduction();
    }
    void reduction(){
        ll g = gcd(n, d);
        n /= g, d /= g;
    }
};

template <typename T>
ostream& operator<<(ostream& os, const frac<T>& f){
    os << f.n << '/' << f.d;
    return os;
}