#include <iostream>

using namespace std;

/**
 * https://kenkoooo.hatenablog.com/entry/2016/11/30/163533
 * より。Project Eularであまりにも使うので。
 */

__int128 parse(string &s) {
  __int128 ret = 0;
  for (int i = 0; i < s.length(); i++)
    if ('0' <= s[i] && s[i] <= '9')
      ret = 10 * ret + s[i] - '0';
  return ret;
}

istream & operator >> (istream &in,  __int128_t &m){
    string s; cin >> s;
    m = parse(s);
    return in;
}


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