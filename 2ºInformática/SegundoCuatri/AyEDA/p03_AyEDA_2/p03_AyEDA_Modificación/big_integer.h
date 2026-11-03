/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º Práctica 03: Calculadora para números grandes                                         
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 11/03/2025                                                                                                    
* Archivo big_integer.h:                                                                                                      
* Declaración de la clase BigInteger                                                                                
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/   

#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include "big_number.h"
#include "big_unsigned.h"
#include "big_rational.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

template <unsigned char Base> class BigNumber;
template <unsigned char Base> class BigUnsigned;

template<unsigned char Base>
class BigInteger : public BigNumber<Base> {
 public:
    // Constructor por defecto (0)
	BigInteger() : abs_value_(BigUnsigned<Base>(0)), is_negative_(false) {}

	// Constructor con número entero
	BigInteger(int n) {
		abs_value_ = BigUnsigned<Base>(n); 
		if (n < 0) {
			is_negative_ = true;
		} else {
			is_negative_ = false;
		}
	}

  // Constructor con BigUnsigned
	BigInteger(const BigUnsigned<Base>& abs_value, bool is_negative = false) : abs_value_(abs_value), is_negative_(is_negative) {}

  // Constructor con cadena de texto
	BigInteger(const std::string& string) {
		if (string[0] == '-') {
			is_negative_ = true;
			abs_value_ = BigUnsigned<Base>(string.substr(1));
		} else {
			is_negative_ = false;
			abs_value_ = BigUnsigned<Base>(string);
		}
	}

  // Operador de igualdad
	friend bool operator==(const BigInteger& big_integer_a, const BigInteger& big_integer_b) {
		return big_integer_a.is_negative_ == big_integer_b.is_negative_ && big_integer_a.abs_value_ == big_integer_b.abs_value_;
	}

	// Operador de menor que
	friend bool operator<(const BigInteger& big_integer_a, const BigInteger& big_integer_b) {
		if (big_integer_a.is_negative_ != big_integer_b.is_negative_) {
			return big_integer_a.is_negative_;
		}
		if (big_integer_a.is_negative_) {
			return big_integer_b.abs_value_ < big_integer_a.abs_value_;
		}
		return big_integer_a.abs_value_ < big_integer_b.abs_value_;
	}

  // Operador de mayor que
	friend bool operator>(const BigInteger& a, const BigInteger& b) {
		return b < a;
	}

	// Sobrecarga del operador de pre-incremento
	BigInteger<Base>& operator++() {
		*this = *this + BigInteger<Base>(1);
		return *this;
	}

	// Sobrecarga del operador de post-incremento
	BigInteger<Base> operator++(int) {
		BigInteger<Base> tmp = *this;
		*this = *this + BigInteger<Base>(1);
		return tmp;
	}

	// Sobrecarga del operador de pre-decremento
	BigInteger<Base>& operator--() {
		*this = *this - BigInteger<Base>(1);
		return *this;
	}

	// Sobrecarga del operador de post-decremento
	BigInteger<Base> operator--(int) {
		BigInteger<Base> tmp = *this;
		*this = *this - BigInteger<Base>(1);
		return tmp;
	}



	// Operador de suma
	friend BigInteger operator+(const BigInteger& big_integer_a, const BigInteger& big_integer_b) {
		if (big_integer_a.is_negative_ == big_integer_b.is_negative_) {
			return BigInteger(big_integer_a.abs_value_ + big_integer_b.abs_value_, big_integer_a.is_negative_);
		} else if (big_integer_a.abs_value_ > big_integer_b.abs_value_) {
			return BigInteger(big_integer_a.abs_value_ - big_integer_b.abs_value_, big_integer_a.is_negative_);
		} else {
			return BigInteger(big_integer_b.abs_value_ - big_integer_a.abs_value_, big_integer_b.is_negative_);
		}
	}

  // Operador de resta
	friend BigInteger operator-(const BigInteger& big_integer_a, const BigInteger& big_integer_b) {
		if (big_integer_a.is_negative_ != big_integer_b.is_negative_) {
			return BigInteger(big_integer_a.abs_value_ + big_integer_b.abs_value_, big_integer_a.is_negative_);
		} else  {
			if (big_integer_a.abs_value_ > big_integer_b.abs_value_) {
				return BigInteger(big_integer_a.abs_value_ - big_integer_b.abs_value_, big_integer_a.is_negative_);
			} else {
				return BigInteger(big_integer_b.abs_value_ - big_integer_a.abs_value_, !big_integer_b.is_negative_);
			}
		}
		
	}

	// Operador de multiplicación
	friend BigInteger operator*(const BigInteger& big_integer_a, const BigInteger& big_integer_b) {
		BigUnsigned<Base> result = big_integer_a.abs_value_ * big_integer_b.abs_value_;
		bool is_negative = (big_integer_a.is_negative_ != big_integer_b.is_negative_);
		return BigInteger<Base>(result, is_negative);
	}

    // Operador de división
	friend BigInteger operator/(const BigInteger& big_integer_a, const BigInteger& big_integer_b) {
		if (big_integer_b.abs_value_ == BigUnsigned<Base>(0)) {
			throw BigNumberDivisionByZero();
		}

		BigUnsigned<Base> result = big_integer_a.abs_value_ / big_integer_b.abs_value_;
		bool is_negative = (big_integer_a.is_negative_ != big_integer_b.is_negative_);
		return BigInteger(result, is_negative);
	}

    // Operador de módulo
	friend BigInteger operator%(const BigInteger& big_integer_a, const BigInteger& big_integer_b) {
		if (big_integer_b.abs_value_ == BigUnsigned<Base>(0)) {
			throw BigNumberDivisionByZero();
		}

		BigUnsigned<Base> result = big_integer_a.abs_value_ % big_integer_b.abs_value_;
		return BigInteger(result, big_integer_a.is_negative_);
	}

  // Operador de salida
	friend std::ostream& operator<<(std::ostream& os, const BigInteger& num) {
		if (num.is_negative_) {
			os << '-';
		}
		os << num.abs_value_;
		return os;
	}

  // Operador de entrada
	friend std::istream& operator>>(std::istream& is, BigInteger& num) {
		std::string input;
		is >> input;
		if (input[0] == '-') {
			num.is_negative_ = true;
			num.abs_value_ = BigUnsigned<Base>(input.substr(1));
			
		} else {
			num.is_negative_ = false;
			num.abs_value_ = BigUnsigned<Base>(input);
		}
		return is;
	}


	friend BigInteger mcd(const BigInteger& big_integer_a, const BigInteger& big_integer_b) {
		BigUnsigned<Base> aux_zero;

		if (big_integer_a == aux_zero && big_integer_b == aux_zero) {
			throw BigNumberUnknownException();
		}

		BigUnsigned<Base> aux1(big_integer_a.abs_value_);
		BigUnsigned<Base> aux2(big_integer_b.abs_value_);

		while (aux2 > aux_zero) {

			if (aux2 == aux_zero) {
				//std::cerr << "aux2 se volvió 0. Terminamos la iteración." << std::endl;
				break;
			}

			BigUnsigned<Base> aux = aux2;
			aux2 = aux1 % aux2;
			aux1 = aux;
		}
		BigInteger<Base> final_result(aux1);
		return final_result;

	}

	BigUnsigned<Base> GetN() const {
		return abs_value_;
	}

	bool Sign() const {
		return is_negative_;
	}

	bool is_zero() const {
		return abs_value_.is_zero();
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

		virtual BigNumbe* copy() const = 0;

	protected:
		virtual std::ostream& write(std::ostream&) const = 0;
		virtual std::istream& read(std::istream&) = 0;
	*/

	BigNumber<Base>& add(const BigNumber<Base>& n1) const {
		const BigInteger<Base> n2 = static_cast<const BigInteger<Base>>(n1);
		//std::cerr << "Suma enteros" << std::endl;
		return *new BigInteger<Base>(*this + n2);
	}

	BigNumber<Base>& subtract(const BigNumber<Base>& n1) const {
		const BigInteger<Base> n2 = static_cast<const BigInteger<Base>>(n1);
		return *new BigInteger<Base>(*this - n2);
	}

	BigNumber<Base>& multiply(const BigNumber<Base>& n1) const {
		const BigInteger<Base> n2 = static_cast<const BigInteger<Base>>(n1);
		return *new BigInteger<Base>(*this * n2);
	}

	BigNumber<Base>& divide(const BigNumber<Base>& n1) const {
		const BigInteger<Base> n2 = static_cast<const BigInteger<Base>>(n1);
		return *new BigInteger<Base>(*this / n2);
	}

	BigNumber<Base>& module(const BigNumber<Base>& n1) const {
		const BigInteger<Base> n2 = static_cast<const BigInteger<Base>>(n1);
		return *new BigInteger<Base>(*this % n2);
	}

	bool operator==(const BigNumber<Base>& n1) const {
		const BigInteger<Base> n2 = static_cast<const BigInteger<Base>>(n1);
		return *this == n2;
	}

	bool operator<(const BigNumber<Base>& n1) const {
		const BigInteger<Base> n2 = static_cast<const BigInteger<Base>>(n1);
		return *this < n2;
	}

	operator BigUnsigned<Base>() const {
		return abs_value_;
	}

	operator BigInteger<Base>() const {
		return *this;
	}

	operator BigRational<Base>() const {
		return BigRational<Base>(*this);
	}

	BigNumber<Base>* copy() const {
		return new BigInteger<Base>(*this);
	}

	std::ostream& write(std::ostream& os) const {
		os << *this << "i";
		return os;
	}

	std::istream& read(std::istream& is) {
		BigInteger<Base> result;
		is >> result;
		*this = result;
		return is;
	}

	

 private:
	BigUnsigned<Base> abs_value_;  // Valor absoluto
	bool is_negative_;             // Indicador de signo
};

#endif