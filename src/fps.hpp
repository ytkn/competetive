#include <vector>
#include <atcoder/modint>
#include <atcoder/convolution>

using namespace std;

using mint = atcoder::modint998244353;


struct FPS: vector<mint>{
    using vector<mint>::vector;
    /**
     * verofied: https://judge.yosupo.jp/submission/137319
     */
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

    FPS dev(){
        FPS ans(this->size()-1);
        for(int i = 1; i < this->size(); i++){
            ans[i-1] = (*this)[i]*i;
        }
        return ans;
    }

    /**
     * verified: https://judge.yosupo.jp/submission/165269
     */
    FPS log(int deg){
        assert((*this)[0].val() == 1);
        FPS f_inv = inv(deg);
        FPS prod = (this->dev())*f_inv;
        FPS ans(deg);
        for(int i = 0; i < deg-1 && i < prod.size(); i++){
            ans[i+1] = prod[i]/(i+1);
        }
        return ans;
    }

    /**
     * verified: https://judge.yosupo.jp/submission/165270
     */
    FPS exp(int deg){
        assert((*this)[0].val() == 0);
        FPS f(1, mint(0));
        FPS g(1, mint(1));
        int d = 1;
        while(f.size() < deg){
            d <<= 1;
            while(f.size() < d) f.push_back((*this)[f.size()]);
            FPS h = f-g.log(d);
            h[0] += 1;
            g = (g*h).mod_deg(d);
        }
        return g.mod_deg(deg);
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