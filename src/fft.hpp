#include <iostream>
#include <complex>
#include <vector>

using namespace std;

const double PI = M_PI;
const complex<double> I(0.0, 1.0);

complex<double> omega(int k, int n){
    return exp(2.0*PI*I*(double)k/(double)n);
}

vector<complex<double>> fft(vector<double> coefs){
    int n = coefs.size();
    if(n == 1) {
        complex<double> x(coefs[0], 0.0);
        return vector<complex<double>>(1, x);
    }
    vector<double> v_even, v_odd;
    for(int i = 0; i < n; i++){
        if(i%2 == 0) v_even.push_back(coefs[i]);
        else v_odd.push_back(coefs[i]);
    }
    auto result_even = fft(v_even);
    auto result_odd = fft(v_odd);
    vector<complex<double>> ans;
    for(int i = 0; i < n; i++){
        ans.push_back(result_even[i%(n/2)] + omega(i, n)*result_odd[i%(n/2)]);
    }
    return ans;
}

vector<complex<double>> inverse_fft(vector<complex<double>> coefs){
    int n = coefs.size();
    if(n == 1) {
        return vector<complex<double>>(1, coefs[0]);
    }
    vector<complex<double>> v_even, v_odd;
    for(int i = 0; i < n; i++){
        if(i%2 == 0) v_even.push_back(coefs[i]);
        else v_odd.push_back(coefs[i]);
    }
    auto result_even = inverse_fft(v_even);
    auto result_odd = inverse_fft(v_odd);
    vector<complex<double>> ans;
    for(int i = 0; i < n; i++){
        ans.push_back(result_even[i%(n/2)] + omega(-i, n)*result_odd[i%(n/2)]);
    }
    return ans;
}

/**
 * 多項式の積を計算 
 */
vector<double> multiply(vector<double> f, vector<double> g){
    int sz = 1;
    while (sz < f.size() + g.size()) sz *= 2;
    vector<double> nf(sz), ng(sz);
    for(int i = 0; i < f.size(); i++) {
        nf[i] = f[i];
        ng[i] = g[i];
    }
    auto result_f = fft(nf);
    auto result_g = fft(ng);
    vector<complex<double>> conv;
    for(int i = 0; i < sz; i++) conv.push_back(result_f[i]*result_g[i]);
    auto mul = inverse_fft(conv);
    vector<double> ans;
    for(complex<double> coef : mul) ans.push_back(coef.real()/sz);
    return ans;
}