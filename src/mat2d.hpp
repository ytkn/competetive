/**
 * matrix.hppは定数倍が遅いので2x2の正方行列しか使わないならこっちのほうがいい。
 */ 
#include "mod_int.hpp"

using mint = ModInt;

struct M {
    mint a00, a01, a10, a11;
};

M m1 = M{
    mint(1), mint(1),
    mint(1), mint(0)
};

M m0 = M{
    mint(0), mint(0),
    mint(1), mint(0)
};

M I = M{
    mint(1), mint(0),
    mint(0), mint(1)
};

M operator*(M m1, M m2){
    return M{
        m1.a00*m2.a00+m1.a01*m2.a10, m1.a00*m2.a01+m1.a01*m2.a11, 
        m1.a10*m2.a00+m1.a11*m2.a10, m1.a10*m2.a01+m1.a11*m2.a11, 
    };
}

M operator^(M m, ll r){
    M ans = I;
    while (r > 0) {
        if (r&1) ans = (ans*m);
        m = (m*m);
        r >>= 1;
    }
    return ans;
}

void print_mat(M mat){
    cout << mat.a00 << ' ' << mat.a01 << endl;
    cout << mat.a10 << ' ' << mat.a11 << endl;
    cout << endl;
}
