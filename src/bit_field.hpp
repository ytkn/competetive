class BitField{
    public:
    bool v;
    BitField(bool _v = false){
        v = _v;
    }
    BitField operator+(bool b){
        return BitField(v|b);
    }
    BitField operator*(bool b){
        return BitField(v&b);
    }

    void operator+=(bool b){
        v |= b;
    }
    void operator*=(bool b){
        v &= b;
    }
    
    
    BitField operator+(BitField b){
        return BitField(v|b.v);
    }
    
    BitField operator*(BitField b){
        return BitField(v&b.v);
    }

    void operator+=(BitField b){
        v |= b.v;
    }
    void operator*=(BitField b){
        v &= b.v;
    }
};

