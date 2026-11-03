/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º Práctica 03: Calculadora para números grandes                                         
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 11/03/2025                                                                                                    
* Archivo big_rational.h:                                                                                                      
* Declaración de la clase BigRational                                                                                  
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/   

#ifndef BIGRATIONAL_H
#define BIGRATIONAL_H

#include "big_integer.h" 
#include "big_unsigned.h"
#include "big_number.h"

#include <iostream>
#include <string>
#include <stdexcept>

template <unsigned char Base> class BigNumber;
template <unsigned char Base> class BigUnsigned;
template <unsigned char Base> class BigInteger;

template <unsigned char Base>
class BigRational : public BigNumber<Base> {
 public:
	BigRational(const BigInteger<Base>& numerator = BigInteger<Base>(0), const BigUnsigned<Base>& denominator = BigUnsigned<Base>(1)) {
		if (denominator == BigUnsigned<Base>(0)) {
			throw BigNumberDivisionByZero();
		}
		BigInteger<Base> aux;
		if (numerator.is_zero() && denominator == BigUnsigned<Base>(1)) {
			aux = BigInteger<Base>(1);
		} else {
			aux = mcd(numerator, BigInteger<Base>(denominator));
		}
		//std::cerr << "mcd exitoso" << std::endl;
		numerator_ = numerator / aux;
		denominator_ = denominator / aux.GetN();
	}

	BigRational(const std::string& string) {
		size_t pos = string.find('/');
		if (pos == std::string::npos) {
			numerator_ = BigInteger<Base>(string);
			denominator_ = BigUnsigned<Base>(1);
		} else {
			if (pos == 0 || pos == string.size() - 1) {
				throw BigNumberEntryError();
			}
			numerator_ = BigInteger<Base>(string.substr(0, pos));
			denominator_ = BigUnsigned<Base>(string.substr(pos + 1));
			if (denominator_.is_zero()) {
				std::cerr << "Error: Denominador es 0" << std::endl;
			}
		}
	}

	BigRational(const BigRational& big_rational) : numerator_{big_rational.numerator_}, denominator_{big_rational.denominator_} {}

	BigRational& operator=(const BigRational& big_rational) {
		numerator_ = big_rational.numerator_;
		denominator_ = big_rational.denominator_;
		return *this;
	}

	friend bool operator==(const BigRational& big_rational_a, const BigRational& big_rational_b) {
		return big_rational_a.numerator_ == big_rational_b.numerator_ && big_rational_a.denominator_ == big_rational_b.denominator_;
	}

	friend bool operator<(const BigRational& big_reational_a, const BigRational& big_rational_b) {
		return big_reational_a.numerator_ * BigInteger<Base>(big_rational_b.denominator_) < big_rational_b.numerator_ * BigInteger<Base>(big_reational_a.denominator_);
	}

	BigRational operator-() const {
		return BigRational(-numerator_, denominator_);
	}

	friend BigRational operator+(const BigRational& big_rational_a, const BigRational& big_rational_b) {
		BigInteger<Base> num = big_rational_a.numerator_ * BigInteger<Base>(big_rational_b.denominator_) + big_rational_b.numerator_ * BigInteger<Base>(big_rational_a.denominator_);
		BigUnsigned<Base> den = big_rational_a.denominator_ * big_rational_b.denominator_;
		return BigRational(num, den);
	}

	friend BigRational operator-(const BigRational& big_rational_a, const BigRational& big_rational_b) {
		BigInteger<Base> num = big_rational_a.numerator_ * BigInteger<Base>(big_rational_b.denominator_) - big_rational_b.numerator_ * BigInteger<Base>(big_rational_a.denominator_);
		BigUnsigned<Base> den = big_rational_a.denominator_ * big_rational_b.denominator_;
		return BigRational(num, den);
	}

	friend BigRational operator*(const BigRational& big_rational_a, const BigRational& big_rational_b) {
		BigInteger<Base> num = big_rational_a.numerator_ * big_rational_b.numerator_;
		BigUnsigned<Base> den = big_rational_a.denominator_ * big_rational_b.denominator_;
		return BigRational(num, den);
	}

	friend BigRational operator/(const BigRational& big_rational_a, const BigRational& big_rational_b) {
		if (big_rational_b.numerator_.is_zero()) {
			throw BigNumberDivisionByZero();
		}
		BigInteger<Base> num = big_rational_a.numerator_ * BigInteger<Base>(big_rational_b.denominator_);
		BigInteger<Base> den = big_rational_b.numerator_ * BigInteger<Base>(big_rational_a.denominator_);
		if (den.Sign()) {
			BigInteger<Base> aux(num.GetN(), true);
			return BigRational<Base>(aux, den.GetN());
		}
		return BigRational<Base>(num, den.GetN());
	}

	friend std::ostream& operator<<(std::ostream& os, const BigRational& big_rational) {
		os << big_rational.numerator_ << '/' << big_rational.denominator_;
		return os;
	}

	friend std::istream& operator>>(std::istream& is, BigRational& big_rational) {
		std::string input;
		is >> input;
		big_rational = BigRational(input);
		return is;
	}

	/*
	virtual BigNumber<Base>& add(const BigNumber<Base>&) const = 0;
	virtual BigNumber<Base>& subtract(const BigNumber<Base>&) const = 0;
	virtual BigNumber<Base>& multiply(const BigNumber<Base>&) const = 0;
	virtual BigNumber<Base>& divide(const BigNumber<Base>&) const = 0;
	virtual bool operator==(const BigNumber&) const = 0;
	virtual bool operator<(const BigNumber&) const = 0;
		
		virtual operator BigUnsigned<Base>() const = 0;
		virtual operator BigInteger<Base>() const = 0;
		virtual operator Bigrational<Base>() const = 0;

		virtual bool is_zero() const = 0;

		virtual BigNumber* copy() const = 0;

	protected:
		virtual std::ostream& write(std::ostream&) const = 0;
		virtual std::istream& read(std::istream&) = 0;
	*/
	BigNumber<Base>& add(const BigNumber<Base>& n1) const {
		const BigRational<Base> n2 = static_cast<const BigRational<Base>>(n1);
		return *new BigRational<Base>(*this + n2);
	}

	BigNumber<Base>& subtract(const BigNumber<Base>& n1) const {
		const BigRational<Base> n2 = static_cast<const BigRational<Base>>(n1);
		return *new BigRational<Base>(*this - n2);
	}

	BigNumber<Base>& multiply(const BigNumber<Base>& n1) const {
		const BigRational<Base> n2 = static_cast<const BigRational<Base>>(n1);
		return *new BigRational<Base>(*this * n2);
	}

	BigNumber<Base>& divide(const BigNumber<Base>& n1) const {
		const BigRational<Base> n2 = static_cast<const BigRational<Base>>(n1);
		return *new BigRational<Base>(*this / n2);
	}

	BigNumber<Base>& module(const BigNumber<Base>& n1) const {
		throw BigNumberRationalModule();
		return *new BigRational<Base>(*this);
	}

	bool operator==(const BigNumber<Base>& n1) const {
		const BigRational<Base> n2 = static_cast<const BigRational<Base>>(n1);
		return *this == n2;
	}

	bool operator<(const BigNumber<Base>& n1) const {
		const BigRational<Base> n2 = static_cast<const BigRational<Base>>(n1);
		return *this < n2;
	}

	operator BigUnsigned<Base>() const {
		BigUnsigned<Base> result = BigUnsigned<Base>(numerator_) / denominator_;
		return result;
	}

	operator BigInteger<Base>() const {
		BigInteger<Base> result = numerator_ / BigInteger<Base>(denominator_);
		return result;
	}

	operator BigRational<Base>() const {
		return *this;
	}

	BigNumber<Base>* copy() const {
		return new BigRational<Base>(*this);
	}

	std::ostream& write(std::ostream& os) const {
		os << *this << "r";
		return os;
	}

	std::istream& read(std::istream& is) {
		BigRational<Base> result;
		is >> result;
		*this = result;
		return is;
	}

	bool is_zero() const {
		return numerator_.is_zero();
	}



 private:
	BigInteger<Base> numerator_;
	BigUnsigned<Base> denominator_;
};

#endif