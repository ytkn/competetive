#include <vector>
#include <iostream>

using namespace std;

template<typename T>
class point{
    T x, y;
};

template<typename T>
ostream& operator<<(ostream& os, const point<T>& p){
    os << p.x << ' ' << p.y;
    return os;
}

/**
 * for sorting by atan2(x, y)
 * verified: https://old.yosupo.jp/submission/36595
 */
template<typename T>
bool comp(point<T> p1, point<T> p2){
    if(p1.y >= 0 && p2.y < 0) return false;
    if(p1.y < 0 && p2.y >= 0) return true;
    if(p1.y == 0 && p2.y == 0) return p1.x >= p2.x;
    if(p1.y == 0 && p1.x == 0) return p2.y >= 0;
    if(p2.y == 0 && p2.x == 0) return p1.y <= 0;
    return p1.y*p2.x < p1.x*p2.y;
}

