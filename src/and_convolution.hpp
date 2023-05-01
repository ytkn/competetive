#include <vector>
#include "zeta_mobius.hpp"

template<typename T>
vector<T> and_convolution(vector<T> u, vector<T> v, int n){
    assert(u.size() == (1<<n));
    assert(v.size() == (1<<n));
    auto prod_sup_sum = supset_zeta(u, n);
    auto v_sup_sum = supset_zeta(v, n);
    for(int i = 0; i < (1<<n); i++){
        prod_sup_sum[i] *= v_sup_sum[i];
    }
    return supset_mobius(prod_sup_sum, n);
}
