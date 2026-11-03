#include "big_rational.h"

BigRational::BigRational(const BigInteger& big_integer, const BigUnsigned& big_unsigned) {
    numerator_ = big_integer;
    denominator_ = big_unsigned;
}

BigRational::BigRational(const BigRational& big_rational) {
    numerator_ = big_rational.numerator_;
    denominator_ = big_rational.denominator_;
}

void BigRational::Simplify() {
    BigInteger denominator(denominator_);
    BigInteger result = mcd(numerator_, denominator);
    numerator_ = numerator_ / result;
    BigInteger aux = denominator / result;
    denominator_ = aux.get_n();
}

bool BigRational::operator==(const BigRational& big_rational) const {
    BigRational aux1 = *this;
    BigRational aux2 = big_rational;
    aux1.Simplify();
    aux2.Simplify();
    return ((aux1.numerator_ == aux2.numerator_) && (aux1.denominator_ == aux2.denominator_));
}

BigRational operator+(const BigRational& big_rational_1, const BigRational& big_rational_2) {
    BigInteger aux1(big_rational_1.denominator_);
    BigInteger aux2(big_rational_2.denominator_);

    BigInteger mcd_result = mcd(aux1, aux2);
    std::cerr << "mcd parcial "<< mcd_result << std::endl;

    std::cerr << "Primera división" << big_rational_1.denominator_ / mcd_result << std::endl;
    std::cerr << "Primera multiplicación " << (big_rational_1.denominator_ / mcd_result) * big_rational_1.numerator_ << std::endl;
    BigInteger numerator_1 = (big_rational_1.denominator_ / mcd_result) * big_rational_1.numerator_;

    std::cerr << "Segunda división" << big_rational_2.denominator_ / mcd_result << std::endl;
    std::cerr << "Primera multiplicación " << (big_rational_2.denominator_ / mcd_result) * big_rational_2.numerator_ << std::endl;
    BigInteger numerator_2 = (big_rational_2.denominator_ / mcd_result) * big_rational_2.numerator_;

    BigInteger numerator_result = numerator_1 + numerator_2;

    BigRational final_result(numerator_result, mcd_result.get_n());
    return final_result;
}

std::ostream& operator<<(std::ostream& os, const BigRational& big_rational) {
    os << "Numerador: " << big_rational.numerator_ << ", Denominador: " << big_rational.denominator_ << ". Resultado: " << big_rational.numerator_ << " / " << big_rational.denominator_ << std::endl;
    return os;
}

