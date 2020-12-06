#include <iostream>

using namespace std;

/**
 * https://kenkoooo.hatenablog.com/entry/2016/11/30/163533
 * より。Project Eularであまりにも使うので。
 */  
ostream &operator<<(std::ostream &dest, __int128_t value) {
    ostream::sentry s(dest);
    if (s) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[128];
        char *d = end(buffer);
        do {
        --d;
        *d = "0123456789"[tmp % 10];
        tmp /= 10;
        } while (tmp != 0);
        if (value < 0) {
        --d;
        *d = '-';
        }
        int len = end(buffer) - d;
        if (dest.rdbuf()->sputn(d, len) != len) {
        dest.setstate(ios_base::badbit);
        }
    }
    return dest;
}