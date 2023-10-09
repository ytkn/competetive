#include <random>

std::random_device rnd;
std::mt19937 mt(rnd());
std::mt19937_64 mt_ll(rnd());

int randint(const int l, const int r){
    return mt()%(r - l) + l;
}

long long randll(const long long l, const long long r){
    return mt_ll()%(r - l) + l;
}
