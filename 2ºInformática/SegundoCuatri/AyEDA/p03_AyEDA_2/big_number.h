/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º Práctica 03: Calculadora para números grandes                                         
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 11/03/2025                                                                                                    
* Archivo big_number.h:                                                                                                      
* Declaración de la clase BigNumber                                                                                
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/   

#ifndef BIG_NUMBER_H
#define BIG_NUMBER_H

#include <iostream>
#include <string>
#include <fstream>

#include "big_unsigned.h"
#include "big_integer.h"
#include "big_rational.h"
#include "big_number_exceptions.h"

template <unsigned char Base = 10> class BigUnsigned;
template <unsigned char Base = 10> class BigInteger;
template <unsigned char Base = 10> class BigRational;

template <unsigned char Base>
class BigNumber {
 public:
 	virtual ~BigNumber() {}

	virtual BigNumber<Base>& add(const BigNumber<Base>&) const = 0;
	BigNumber& operator+(const BigNumber& n) const {
		return add(n);
	}

	virtual BigNumber<Base>& subtract(const BigNumber<Base>&) const = 0;
  BigNumber& operator-(const BigNumber& n) const {
		return substract(n);
	}

	virtual BigNumber<Base>& multiply(const BigNumber<Base>&) const = 0;
	BigNumber& operator*(const BigNumber& n) const {
		return multiply(n);
	}

	virtual BigNumber<Base>& divide(const BigNumber<Base>&) const = 0;
  BigNumber& operator/(const BigNumber& n) const {
		return divide(n);
	}

	friend std::ostream& operator<<(std::ostream& os, const BigNumber<Base>& n) {
		return n.write(os);
	}
	friend std::istream& operator>>(std::istream& is, BigNumber<Base>& n) {
		return n.read(is);
	}

	static BigNumber<Base>* create(const std::string& string) {
		if (string.empty()) {
			throw BigNumberEntryError();
		}
		switch(string.back()) {
			case 'r': return new BigRational<Base>(string.substr(0, string.length() - 1));
			case 'i': return new BigInteger<Base>(string.substr(0, string.length() - 1));
			case 'u': return new BigUnsigned<Base>(string.substr(0, string.length() - 1));
			default: throw BigNumberEntryError();
		}
	}

	bool operator!=(const BigNumber& n) const {
		return !(*this == n);
	}

 	bool operator>(const BigNumber& n) const {
		return n < *this;
	}

  bool operator<=(const BigNumber& n) const {
		return !(n < *this);
	}

  bool operator>=(const BigNumber& n) const {
		return !(*this < n);
	}

	virtual bool operator==(const BigNumber&) const = 0;
  virtual bool operator<(const BigNumber&) const = 0;
	 
	virtual operator BigUnsigned<Base>() const = 0;
	virtual operator BigInteger<Base>() const = 0;
	virtual operator BigRational<Base>() const = 0;

  virtual bool is_zero() const = 0;

	virtual BigNumber* copy() const = 0;

 protected:
	virtual std::ostream& write(std::ostream&) const = 0;
	virtual std::istream& read(std::istream&) = 0;
 
};

#endif