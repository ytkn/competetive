#include <vector>
#include <iostream>
#include <cassert>

using namespace std;


// calc a//b 
template<typename T>
T ceil_div(T a, T b){
    return (a+b-1)/b;
}

template<typename T>
vector<T> add_vector(vector<T> u, vector<T> v){
    assert(u.size() == v.size());
    int n = u.size();
    vector<T> ans(n);
    for(int i = 0; i < n; i++) ans[i] = u[i]+v[i];
    return ans;
}

template<typename T>
vector<T> pointwise_product(vector<T> u, vector<T> v){
    assert(u.size() == v.size());
    int n = u.size();
    vector<T> ans(n);
    for(int i = 0; i < n; i++) ans[i] = u[i]*v[i];
    return ans;
}

template<typename T>
void print_vector(vector<T> v, char delimiter=' '){
    for(int i = 0; i+1 < v.size(); i++) cout << v[i] << delimiter;
    cout << v.back() << endl;
}