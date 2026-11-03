#ifndef BIGRATIONAL_H
#define BIGRATIONAL_H

#include "big_integer.h"
#include "big_unsigned.h"

class BigRational {
 public:
	BigRational(const BigInteger& = 0, const BigUnsigned& = 1);
	BigRational(const BigRational&);

	bool operator==(const BigRational&) const;
	friend std::ostream& operator<<(std::ostream&, const BigRational&);

	friend BigRational operator+(const BigRational&, const BigRational&);

	void Simplify();
 private:
	BigInteger numerator_;
	BigUnsigned denominator_;
	
};

#endif