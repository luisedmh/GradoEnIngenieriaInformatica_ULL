template <unsigned char Base>
class BigUnsigned {
    template<>
    friend ostream& operator<<<Base>(const ostream& os, const BigUnsigned& bi);
    
};