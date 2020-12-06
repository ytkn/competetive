#include <iostream>

using namespace std;

/**
 * std::complex使えば? 
 */
template <typename T>
class complex{
    public:
    T r;
    T i;
    complex(T _r, T _i){
        r = _r; i = _i;
    }
    complex operator*(complex c){
        return complex(c.r*r-c.i*i, c.r*i+c.i*r);
    }
    complex conjugate(){
        return complex(r, -i);
    }
    void operator*=(complex c){
        T r_ = r, i_ = i;
        r = r_*c.r-i_*c.i;
        i = r_*c.i+i_*c.r;
    }
};


template <typename T>
ostream& operator<<(ostream& os, const complex<T>& c){
    os << c.r << '+' << c.i << 'i';
    return os;
}