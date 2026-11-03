/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática* Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º* Práctica 01: Representación de números grandes                                          
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 11/02/2025                                                                                                    
* Archivo big_integer.cc:                                                                                                      
* Implementación de la clase BigInteger                                                                                
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/  

#include "big_integer.h"

BigInteger::BigInteger(int n) {
	sign_ = n < 0;
	BigUnsigned result = (sign_) ? -1 * n : n;
	n_ = result;
}

void BigInteger::RemoveZeros() {
	n_.RemoveZeros();
}

BigInteger::BigInteger(const std::string& string) {
	if (string.empty()) {
		std::cerr << "Error: cadena de entrada vacía" << std::endl;
		exit(-1);
	}
	if (string[0] == '+' || string[0] == '-') {
		sign_ = (string[0] == '-');
		n_ = BigUnsigned(string.substr(1));
	} else {
		sign_ = 0;
		n_ = BigUnsigned(string);
	}
	
	RemoveZeros();
}


BigInteger::BigInteger(const BigUnsigned& big_unsigned) {
	n_ = big_unsigned;
	sign_ = 0;
}

BigInteger::BigInteger(const BigUnsigned& big_unsigned, const bool sign) {
	n_ = big_unsigned;
	sign_ = sign;
}

BigInteger::BigInteger(const BigInteger& big_integer) {
	n_ = big_integer.n_;
	sign_ = big_integer.sign_;
}

BigInteger& BigInteger::operator=(const BigInteger& big_integer) {
	n_ = big_integer.n_;
	sign_ = big_integer.sign_;
	return *this;
}

bool BigInteger::operator==(const BigInteger& big_integer) const {
	if ((sign_ != big_integer.sign_)) {
		return false;
	} else {
		return big_integer.n_ == n_;
	}
}

BigInteger& BigInteger::operator++() {
	BigInteger adder(1);
	*this = *this + adder;
	return(*this);
}

BigInteger BigInteger::operator++(int) {
	BigInteger aux(*this);
	++(*this);
	return(aux);
}

BigInteger& BigInteger::operator--() {
	BigInteger subs(1);
	*this = *this - subs;
	return(*this);
}

BigInteger BigInteger::operator--(int) {
	BigInteger aux(*this);
	--(*this);
	return (aux);
}

std::ostream& operator<<(std::ostream& os, const BigInteger& big_integer) {
	if (big_integer.sign_ == 0) {
		os << '+';
	} else {
		os << '-';
	}
	os << big_integer.n_;
	return os;
}

std::istream& operator>>(std::istream& is, BigInteger& big_integer) {
	std::string aux;
	is >> aux; 
	//std::cout << aux << std::endl;
	big_integer = BigInteger(aux);	
	return is;
}

bool operator<(const BigInteger& big_integer_1, const BigInteger& big_integer_2) {
	bool sign_1 = big_integer_1.sign_;
	bool sign_2 = big_integer_2.sign_;
	if (sign_1 != sign_2) {
		return !sign_1;
	} else {
		if (!sign_1) {
			return big_integer_1.n_ < big_integer_2.n_;
		} else {
			return (!(big_integer_1.n_ < big_integer_2.n_) && !(big_integer_1.n_ == big_integer_1.n_));
		}
	}
}

BigInteger operator+(const BigInteger& big_integer_1, const BigInteger& big_integer_2) {
	bool sign1 = big_integer_1.sign_;
	bool sign2 = big_integer_2.sign_;

	BigUnsigned big_unsigned_1 = big_integer_1.n_;
	BigUnsigned big_unsigned_2 = big_integer_2.n_;
	
	if (sign1 == sign2) {
		BigInteger result(big_unsigned_1 + big_unsigned_2, sign1);
		return result;
	} else {
		if (big_unsigned_1 < big_unsigned_2) {
			BigInteger result(big_unsigned_2 - big_unsigned_1, sign2);
			return result;
		} else {
			BigInteger result(big_unsigned_1 - big_unsigned_2, sign1);
			return result;
		}
	}
}

BigInteger operator-(const BigInteger& big_integer_1, const BigInteger& big_integer_2) {
	BigInteger aux(big_integer_2.n_, !big_integer_2.sign_);
	return big_integer_1 + (aux);
}

BigInteger operator*(const BigInteger& big_integer_1, const BigInteger& big_integer_2) {
	BigInteger result(big_integer_1.n_ * big_integer_2.n_, big_integer_1.sign_ != big_integer_2.sign_);
	return result;
}

BigInteger operator/(const BigInteger& big_integer_1, const BigInteger& big_integer_2) {
	BigInteger result(big_integer_1.n_ / big_integer_2.n_, big_integer_1.sign_ != big_integer_2.sign_);
	return result;
}

BigInteger operator%(const BigInteger& big_integer_1, const BigInteger& big_integer_2) {
	BigInteger result(big_integer_1.n_ % big_integer_2.n_, big_integer_1.sign_);
	return result;
}

BigInteger mcd(const BigInteger& big_integer_1, const BigInteger& big_integer_2) {
	BigUnsigned aux_zero;

	if (big_integer_1 == aux_zero && big_integer_2 == aux_zero) {
		std::cerr << "Error: No se puede calcular el MCD de 0 y 0" << std::endl;
		exit(-1);
	}

	BigUnsigned aux1(big_integer_1.n_);
	BigUnsigned aux2(big_integer_2.n_);

	while (aux2 > aux_zero) {
		//std::cerr << "aux1: " << aux1 << ", aux2: " << aux2 << std::endl;

		if (aux2 == aux_zero) {
			std::cerr << "aux2 se volvió 0. Terminamos la iteración." << std::endl;
			break;
		}

		BigUnsigned aux = aux2;
		aux2 = aux1 % aux2;
		aux1 = aux;
	}

	return BigInteger(aux1);
}

