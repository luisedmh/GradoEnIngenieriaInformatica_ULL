/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática* Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º* Práctica 01: Representación de números grandes                                          
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 11/02/2025                                                                                                    
* Archivo big_unsigned.cc:                                                                                                      
* Implementación de la clase BigUnsigned                                                                                  
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/   

#include "big_unsigned.h"

BigUnsigned::BigUnsigned(unsigned n) {
  if (n == 0) {
		n_.push_back(n);
	} else {
		while (n > 0) {
			n_.push_back(n % 10);
			n /= 10;
		}
	}
}

// Función extra para borrar todos los 0 que no afectan al número
void BigUnsigned::RemoveZeros() {
	while (n_.size() > 1 && n_.back() == 0) {
  	n_.pop_back();
	}
}

BigUnsigned::BigUnsigned(const std::string& string) {
  int length = string.length();
	
	if (length == 0) {
    std::cerr << "Error: La cadena está vacía" << std::endl;
    exit(-1);
  }

  for (int i = length - 1; i >= 0; i--) {
		//std::cout << string[i];
		//std::cout << string.size();
		//std::cout << i << std::endl;
    if (string[i] < '0' || string[i] > '9') {
			std::cerr << "Error, la cadena no es exclusivamente numérica" << std::endl;
			exit(-1);
		} else {
			//std::cout << string[i] << std::endl;
      n_.push_back(string[i] - '0');
		}
  }

  RemoveZeros();
}

BigUnsigned::BigUnsigned(const BigUnsigned& big_unsigned) {
	n_ = big_unsigned.n_;
	RemoveZeros();
}

BigUnsigned::BigUnsigned(const std::vector<unsigned char>& n) : n_{n} {}

BigUnsigned& BigUnsigned::operator=(const BigUnsigned& big_unsigned ) {
	n_ = big_unsigned.n_;
	return *this;
}

bool BigUnsigned::operator==(const BigUnsigned& big_unsigned) const {
	return n_ == big_unsigned.n_;
}

BigUnsigned& BigUnsigned::operator++() {
	BigUnsigned adder(1);
	*this = *this + adder;
	return(*this);
}

BigUnsigned BigUnsigned::operator++(int) {
	BigUnsigned aux(*this);
	++(*this);
	return(aux);
}

BigUnsigned& BigUnsigned::operator--() {
	BigUnsigned subs(1);
	*this = *this - subs;
	return(*this);
}

BigUnsigned BigUnsigned::operator--(int) {
	BigUnsigned aux(*this);
	--(*this);
	return (aux);
}

std::ostream& operator<<(std::ostream& os, const BigUnsigned& big_unsigned) {
	for (int i = big_unsigned.n_.size() - 1; i >= 0; i--) {
		os << (char)(big_unsigned.n_[i] + '0');
	}
	return os;
}

std::istream& operator>>(std::istream& is, BigUnsigned& big_unsigned) {
	std::string aux;
	is >> aux; 
	big_unsigned = BigUnsigned(aux);	
	return is;
}

bool operator<(const BigUnsigned& big_unsigned_1, const BigUnsigned& big_unsigned_2) {
    BigUnsigned aux1(big_unsigned_1);
    aux1.RemoveZeros();
    BigUnsigned aux2(big_unsigned_2);
    aux2.RemoveZeros();

    if (aux1.n_.size() < aux2.n_.size()) return true;
    if (aux1.n_.size() > aux2.n_.size()) return false;

    // Comparar de izquierda a derecha (dígitos más significativos primero)
    for (int i = aux1.n_.size() - 1; i >= 0; --i) {
        if (aux1.n_[i] < aux2.n_[i]) return true;
        if (aux1.n_[i] > aux2.n_[i]) return false;
    }

    return false; // Si son iguales, no es menor
}


bool operator>(const BigUnsigned& big_unsigned_1, const BigUnsigned& big_unsigned_2) {
	if (big_unsigned_1 == big_unsigned_2) {
		return false;
	}
	return !(big_unsigned_1 < big_unsigned_2);
}


BigUnsigned operator+(const BigUnsigned& big_unsigned_1, const BigUnsigned& big_unsigned_2) {
	BigUnsigned final_result;
	std::vector<unsigned char> n1 = big_unsigned_1.n_;
	std::vector<unsigned char> n2 = big_unsigned_2.n_;
	size_t size_n1 = n1.size();
	size_t size_n2 = n2.size();
	size_t biggest_size = (size_n1 < size_n2) ? size_n2 : size_n1;
	unsigned char carry;
	for (size_t i{0}; i < biggest_size; i++) {
		unsigned char aux1, aux2, adder;
		if (i < size_n1) {
			aux1 = n1[i];
		} else {
			aux1 = 0;
		}
		if (i < size_n2) {
			aux2 = n2[i];
		} else {
			aux2 = 0;
		}
		adder = aux1 + aux2 + carry;
		carry = adder / 10;
		final_result.n_.push_back(adder % 10);
	}
	if (carry > 0) {
		final_result.n_.push_back(carry);
	}
	final_result.RemoveZeros();
	return final_result;
}


BigUnsigned operator-(const BigUnsigned& big_unsigned_1, const BigUnsigned& big_unsigned_2) {
	if (big_unsigned_1 < big_unsigned_2) {
			std::cerr << "Error: No es posible realizar esta resta" << std::endl;
			exit(-1);
	}

	std::vector<unsigned char> final_result;
	
	std::vector<unsigned char> n1 = big_unsigned_1.n_;
	std::vector<unsigned char> n2 = big_unsigned_2.n_;
	
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
			unsigned char half_result = 10 + aux1 - aux2 - subs_aux;
			final_result.push_back(half_result);
			subs_aux = 1;
		} else {
			unsigned char half_result = aux1 - aux2 - subs_aux;
			final_result.push_back(half_result);
			subs_aux = 0;
		}
	}
	BigUnsigned result(final_result);
	result.RemoveZeros();
	return result;
}

BigUnsigned operator*(const BigUnsigned& big_unsigned_1, const BigUnsigned& big_unsigned_2) {
    std::vector<unsigned char> n1 = big_unsigned_1.n_;
    std::vector<unsigned char> n2 = big_unsigned_2.n_;

    unsigned size_n1 = n1.size();
    unsigned size_n2 = n2.size();
    
    if ((size_n1 == 1 && n1[0] == 0) || (size_n2 == 1 && n2[0] == 0)) {
        return BigUnsigned(0);
    }

    std::vector<unsigned char> result(size_n1 + size_n2, 0);

    for (unsigned i = 0; i < size_n1; i++) {
        unsigned carry = 0;
        for (unsigned j = 0; j < size_n2; j++) {
            unsigned product = result[i + j] + n1[i] * n2[j] + carry;
            result[i + j] = product % 10;
            carry = product / 10;
        }
        if (carry) {
            result[i + size_n2] += carry;
        }
    }

    BigUnsigned final_result(result);
    final_result.RemoveZeros();
    return final_result;
}


BigUnsigned operator/(const BigUnsigned& dividend, const BigUnsigned& divisor) {
    if (divisor.n_.size() == 1 && divisor.n_[0] == 0) {
        std::cerr << "Error: División por cero" << std::endl;
        exit(-1);
    }

    if (dividend < divisor) {
        return BigUnsigned(0);
    }

    BigUnsigned quotient;
    BigUnsigned remainder;
    
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

BigUnsigned operator%(const BigUnsigned& a, const BigUnsigned& b) {
	if (b == BigUnsigned(0)) {
		std::cerr << "Error: División por cero en operador %" << std::endl;
		exit(-1);
	}

	if (a < b) {  
		return a;
	}

	BigUnsigned result = a;
	while (!(result < b)) {
		result = result - b;
	}

	return result;
}


