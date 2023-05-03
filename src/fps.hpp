#include <vector>
#include <atcoder/modint>
#include <atcoder/convolution>

using namespace std;

using mint = atcoder::modint998244353;

struct FPS: vector<mint>{
    using vector<mint>::vector;
    FPS inv(int deg){
        FPS ans(deg);
        ans[0] = mint(1)/(*this)[0];
        for(int d = 1; d < deg; d<<=1){
            vector<mint> f(2*d), g(2*d);
            for(int i = 0; i < min(2*d, (int)this->size()); i++) f[i] = (*this)[i];
            for(int i = 0; i < d; i++) g[i] = ans[i];
            f = atcoder::convolution(g, atcoder::convolution(g, f));
            for(int i = d; i < min(2*d, deg); i++) ans[i] = -f[i];
        }
        return ans;
    }

    void shrink() {
        while (this->size() && this->back() == mint(0)) this->pop_back();
    }

    FPS& operator*=(const FPS &r){
        if(this->empty() || r.empty()){
            this->clear();
            return *this;
        }
        auto ret = atcoder::convolution(*this, r);
        return *this = FPS(ret.begin(), ret.end());
    }

    FPS& operator+=(const FPS &r){
       if(this->size() < r.size()) this->resize(r.size());
       for(int i = 0; i < (int)r.size(); i++) (*this)[i] += r[i];
        return *this;
    }

    FPS& operator-=(const FPS &r){
       if(this->size() < r.size()) this->resize(r.size());
       for(int i = 0; i < (int)r.size(); i++) (*this)[i] -= r[i];
        return *this;
    }

    FPS operator*(const FPS &r) const { 
        return FPS(*this) *= r; 
    }

    FPS operator+(const FPS &r) const { 
        return FPS(*this) += r; 
    }

    FPS operator-(const FPS &r) const { 
        return FPS(*this) -= r; 
    }

    FPS mod_deg(int deg){
        FPS ret(deg);
        for(int i = 0; i < min(deg, (int)this->size()); i++) ret[i] = (*this)[i];
        return ret;
    }
};
