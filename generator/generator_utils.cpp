#include <random>

std::random_device rnd;
std::mt19937 mt(rnd());

int randint(const int l, const int r){
    return mt()%(r - l) + l;
}