/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º Práctica 03: Calculadora para números grandes                                         
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 11/03/2025                                                                                                    
* Archivo big_unsigned.h:                                                                                                      
* Declaración de la clase BigUnsigned                                                                                  
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/   

#ifndef BIGUNSIGNED_H
#define BIGUNSIGNED_H

#include "big_number_exceptions.h"
#include "big_number.h"
#include "big_integer.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// --------------------------
// Plantilla genérica
// --------------------------
template<unsigned char Base>
class BigUnsigned : public BigNumber<Base> {
 public:
	BigUnsigned(unsigned n = 0) {
    do {
			n_.push_back(n % Base);
			//std::cerr << n % Base << std::endl;
			n /= Base;
    } while (n > 0);
	}
	
	void RemoveZeros() {
		while (n_.size() > 1 && n_.back() == 0) {
			n_.pop_back();
		}
	}

	BigUnsigned(const std::string& string) {
    int size = string.size();
    for (int i = size - 1; i >= 0; --i) {
			char c = string[i];
			unsigned char digit = (c >= '0' && c <= '9') ? (c - '0') : (c - 'A' + 10);
				if (digit >= Base) {
					throw BigNumberBadDigit("Error: Dígito '" + std::string(1, c) + "' no válido para la base " + std::to_string(Base));
				}
			n_.push_back(digit);
			//std::cerr << "Dígito empujado: " << digit + '0' << std::endl;
    }
	}

	BigUnsigned(const BigUnsigned& big_unsigned) : n_(big_unsigned.n_) {}

	BigUnsigned& operator=(const BigUnsigned& big_unsigned) {
		n_ = big_unsigned.n_;
		return *this;
	}

	bool operator==(const BigUnsigned& big_unsigned) const {
		return n_ == big_unsigned.n_;
	}

	friend bool operator<(const BigUnsigned& big_unsigned_a, const BigUnsigned& big_unsigned_b) {
    if (big_unsigned_a.n_.size() != big_unsigned_b.n_.size()) {
			return big_unsigned_a.n_.size() < big_unsigned_b.n_.size();
		}
    for (size_t i = big_unsigned_a.n_.size(); i > 0; --i) {
			if (big_unsigned_a.n_[i - 1] != big_unsigned_b.n_[i - 1]) {
				return big_unsigned_a.n_[i - 1] < big_unsigned_b.n_[i - 1];
			}
    }
    return false;
	}


	friend bool operator>(const BigUnsigned& big_unsigned_a, const BigUnsigned& big_unsigned_b) {
		return big_unsigned_b < big_unsigned_a;
	}




	friend std::ostream& operator<<(std::ostream& os, const BigUnsigned& num) {
    // Verificar si el número está vacío
    if (num.n_.empty()) {
			os << '0';  // Si el número es vacío, es 0
			return os;
    }

    // Imprimir los dígitos de derecha a izquierda
    for (int i = num.n_.size() - 1; i >= 0; --i) {
			os << (char)((num.n_[i] < 10) ? ('0' + num.n_[i]) : ('A' + (num.n_[i] - 10)));
    }
    return os;
	}

	friend std::istream& operator>>(std::istream& is, BigUnsigned& num) {
    std::string input;
    is >> input;
    num = BigUnsigned<Base>(input);
    return is;
	}

	// Sobrecarga del operador de pre-incremento
	BigUnsigned<Base>& operator++() {
		*this = *this + BigUnsigned<Base>(1);
		return *this;
	}

	// Sobrecarga del operador de post-incremento
	BigUnsigned<Base> operator++(int) {
		BigUnsigned<Base> tmp = *this;
		*this = *this + BigUnsigned<Base>(1);
		return tmp;
	}

	// Sobrecarga del operador de pre-decremento
	BigUnsigned<Base>& operator--() {
		if (*this > BigUnsigned<Base>(0)) *this = *this - BigUnsigned<Base>(1);
		return *this;
	}

	// Sobrecarga del operador de post-decremento
	BigUnsigned<Base> operator--(int) {
		if (*this == BigUnsigned<Base>(0)) return *this;
		BigUnsigned<Base> tmp = *this;
		*this = *this - BigUnsigned<Base>(1);
		return tmp;
	}


	friend BigUnsigned operator+(const BigUnsigned&big_unsigned_a, const BigUnsigned& big_unsigned_b) {
		BigUnsigned final_result;
		final_result.n_.pop_back();
		std::vector<unsigned char> n1 = big_unsigned_a.n_;
		std::vector<unsigned char> n2 = big_unsigned_b.n_;
		size_t size_n1 = n1.size();
		size_t size_n2 = n2.size();
		size_t biggest_size = (size_n1 < size_n2) ? size_n2 : size_n1;
		unsigned char carry = 0;
		for (size_t i{0}; i <= biggest_size; i++) {
			unsigned char aux1, aux2, adder;
			if (i < size_n1) {
				aux1 = n1[i];
			} else {
				aux1 = 0;
			}
			//std::cerr << "aux1 = " << aux1 + '0' << std::endl;
			if (i < size_n2) {
				aux2 = n2[i];
			} else {
				aux2 = 0;
			}
			//std::cerr << "aux2 = " << aux2 + '0' << std::endl;
			//std::cerr << "carry = " << carry + '0' << std::endl;
			adder = aux1 + aux2 + carry;
			//std::cerr << "adder = " << adder + '0' << std::endl;
			carry = adder / Base;
			unsigned char result = adder % Base;
			//std::cerr << "result = " << result + '0' << std::endl;
			final_result.n_.push_back(result);
		}
		if (carry > 0) {
			final_result.n_.push_back(carry);
		}
		final_result.RemoveZeros();
		return final_result;
	}


	friend BigUnsigned operator-(const BigUnsigned& big_unsigned_a, const BigUnsigned&big_unsigned_b) {
		if (big_unsigned_a < big_unsigned_b) {
			throw BigNumberUnknownException();
		}

		BigUnsigned<Base> result;
		result.n_.pop_back();
		
		std::vector<unsigned char> n1 = big_unsigned_a.n_;
		std::vector<unsigned char> n2 = big_unsigned_b.n_;
		
		int size_n1 = n1.size();
		int size_n2 = n2.size();

		unsigned char subs_aux = 0;
		
		for (int i{0}; i < size_n1; i++) {
			unsigned char aux1 = n1[i];
			unsigned char aux2;
			if (i < size_n2) {
				aux2 = n2[i];
			} else {
				aux2 = 0;
			}

			if (aux1 < aux2 + subs_aux) {
				unsigned char half_result = Base + aux1 - aux2 - subs_aux;
				result.n_.push_back(half_result);
				subs_aux = 1;
			} else {
				unsigned char half_result = aux1 - aux2 - subs_aux;
				result.n_.push_back(half_result);
				subs_aux = 0;
			}
		}
		result.RemoveZeros();
		return result;
	}


	friend BigUnsigned operator*(const BigUnsigned& big_unsigned_a, const BigUnsigned& big_unsigned_b) {
		std::vector<unsigned char> n1 = big_unsigned_a.n_;
    std::vector<unsigned char> n2 = big_unsigned_b.n_;

		BigUnsigned<Base> result;
		result.n_.pop_back();

    unsigned size_n1 = n1.size();
    unsigned size_n2 = n2.size();
    
    if ((size_n1 == 1 && n1[0] == 0) || (size_n2 == 1 && n2[0] == 0)) {
			return BigUnsigned(0);
    }

    result.n_.resize(size_n1 + size_n2, 0);

    for (unsigned i = 0; i < size_n1; i++) {
			unsigned carry = 0;
			for (unsigned j = 0; j < size_n2; j++) {
				unsigned product = result.n_[i + j] + n1[i] * n2[j] + carry;
				result.n_[i + j] = product % Base;
				carry = product / Base;
			}
			if (carry) {
				result.n_[i + size_n2] += carry;
			}
    }

    result.RemoveZeros();
    return result;
	}




	friend BigUnsigned operator/(const BigUnsigned& dividend, const BigUnsigned& divisor) {
		if (divisor.n_.size() == 1 && divisor.n_[0] == 0) {
			std::cerr << "Error: División por cero" << std::endl;
			throw BigNumberDivisionByZero();
		}

		if (dividend < divisor) {
			return BigUnsigned<Base>(0);
		}

		BigUnsigned<Base> quotient;
		BigUnsigned<Base> remainder;
	
		for (int i = dividend.n_.size() - 1; i >= 0; --i) {
			remainder.n_.insert(remainder.n_.begin(), dividend.n_[i]);
			remainder.RemoveZeros();

			int count = 0;
			while (!(remainder < divisor)) {
				remainder = remainder - divisor;
				count++;
			}
			quotient.n_.insert(quotient.n_.begin(), count);
		}

		quotient.RemoveZeros();
		return quotient;
	}


	friend BigUnsigned operator%(const BigUnsigned& big_unsigned_a, const BigUnsigned& big_unsigned_b) {
		if (big_unsigned_b == BigUnsigned<Base>(0)) {
			throw BigNumberDivisionByZero();
		}
	
		if (big_unsigned_a < big_unsigned_b) {  
			return big_unsigned_a;
		}
	
		BigUnsigned result = big_unsigned_a;
		while (!(result < big_unsigned_b)) {
			result = result - big_unsigned_b;
		}
	
		return result;
	}

	std::vector<unsigned char> GetN() const {
		return n_;
	}

	bool is_zero() const {
		return n_.size() == 1 && n_[0] == 0;
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
		const BigUnsigned<Base> n2 = static_cast<const BigUnsigned<Base>>(n1);
		//std::cerr << "Suma naturales" << std::endl;
		return *new BigUnsigned<Base>(*this + n2);
	}

	BigNumber<Base>& subtract(const BigNumber<Base>& n1) const {
		const BigUnsigned<Base> n2 = static_cast<const BigUnsigned<Base>>(n1);
		return *new BigUnsigned<Base>(*this - n2);
	}

	BigNumber<Base>& multiply(const BigNumber<Base>& n1) const {
		const BigUnsigned<Base> n2 = static_cast<const BigUnsigned<Base>>(n1);
		return *new BigUnsigned<Base>(*this * n2);
	}

	BigNumber<Base>& divide(const BigNumber<Base>& n1) const {
		const BigUnsigned<Base> n2 = static_cast<const BigUnsigned<Base>>(n1);
		return *new BigUnsigned<Base>(*this / n2);
	}

	BigNumber<Base>& module(const BigNumber<Base>& n1) const {
		const BigUnsigned<Base> n2 = static_cast<const BigUnsigned<Base>>(n1);
		return *new BigUnsigned<Base>(*this % n2);
	}

	bool operator==(const BigNumber<Base>& n1) const {
		const BigUnsigned<Base> n2 = static_cast<const BigUnsigned<Base>>(n1);
		return *this == n2;
	}

	bool operator<(const BigNumber<Base>& n1) const {
		const BigUnsigned<Base> n2 = static_cast<const BigUnsigned<Base>>(n1);
		return *this < n2;
	}

	operator BigUnsigned<Base>() const {
		return *this;
	}

	operator BigInteger<Base>() const {
		return BigInteger<Base>(*this);
	}

	operator BigRational<Base>() const {
		return BigRational<Base>(BigInteger<Base>(*this));
	}

	BigNumber<Base>* copy() const {
		return new BigUnsigned<Base>(*this);
	}

	std::ostream& write(std::ostream& os) const {
		os << *this << "u";
		return os;
	}

	std::istream& read(std::istream& is) {
		BigUnsigned<Base> result;
		is >> result;
		*this = result;
		return is;
	}

 private:
	std::vector<unsigned char> n_;  // Genérico
};


#endif
