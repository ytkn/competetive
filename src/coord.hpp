#include <iostream>
#include <cmath>

using namespace std;

template<typename T>
struct line {
    line(T a, T b, T c): a(a), b(b), c(c){};
    T a, b, c;
};

template<typename T>
ostream& operator<<(ostream& os, const line<T>& l){
    os << l.a << "*x + " << l.b << "*y+ " << l.c;
    return os;
}

template<typename T>
inline T add(T a, T b){
    return a+b;
}

const double eps = 1e-10;

inline double add(double a, double b){
    if(abs(a+b) < eps*(abs(a)+abs(b))) return 0.0;
    return a+b;
}

template<typename T>
class point {
    public:
    point<T>(T x, T y): x(x), y(y){};
    point<T>(): x(0), y(0){};
    T x, y;
    point<T> operator + (point<T> p){
        return point<T>(add(x, p.x), add(y, p.y));
    };
    point<T> operator - (point<T> p){
        return point<T>(add(x, -p.x), add(y, -p.y));
    };
    point<T> operator * (T d){
        return point<T>(x*d, y*d);
    };
    T dot(point<T> p){
        return add(x*p.x, y*p.y);
    };
    T det(point<T> p){
        return add(x*p.y, -y*p.x);
    };
};

/**
 * 直線lとp1, p2を結ぶ直線を求めます
 */ 
template<typename T>
line<T> from_points(point<T> p1, point<T> p2){
    return line(p2.y-p1.y, p1.x-p2.x, p1.y*p2.x-p1.x*p2.y);
}

/**
 * l: ax+by+c = 0としたときにax+by+cの値を返します
 */ 
template<typename T>
T substitute(line<T> l, point<T> p){
    return p.x*l.a+p.y*l.b+l.c;
}

/**
 * 直線lとp1, p2を結ぶ線分が交点を持つか否かを返します
 */ 
template<typename T>
bool intersect(line<T> l, point<T> p1, point<T> p2){
    return (substitute(l, p1) > 0) ^ (substitute(l, p2) > 0);
}

/**
 * p1, p2を結ぶ線分とq1, q2を結ぶ線分が交点を持つか否かを返します
 */ 
template<typename T>
bool intersect(point<T> p1, point<T> p2, point<T> q1, point<T> q2){
    auto lp = from_points(p1, p2);
    auto lq = from_points(q1, q2);
    bool fq = (substitute(lq, p1) > 0) ^ (substitute(lq, p2) > 0);
    bool fp = (substitute(lp, q1) > 0) ^ (substitute(lp, q2) > 0);
    return fp&&fq;
}

template<typename T>
double dist(point<T> p1, point<T> p2){
    T dx = p1.x-p2.x;
    T dy = p1.y-p2.y;
    return sqrt(dx*dx+dy*dy);
}
