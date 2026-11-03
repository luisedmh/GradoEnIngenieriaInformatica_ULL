/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática* Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º* Práctica 01: Representación de números grandes                                          
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 11/02/2025                                                                                                    
* Archivo big_integer.h:                                                                                                      
* Declaración de la clase BigInteger                                                                                
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/   

#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <cstring>

#include "big_unsigned.h"

class BigInteger {
 public:
	BigInteger(int n = 0);
	BigInteger(const std::string&);
	BigInteger(const BigUnsigned&);
	BigInteger(const BigUnsigned&, const bool);
	BigInteger(const BigInteger&);

	BigInteger& operator=(const BigInteger&);
	bool operator==(const BigInteger&) const;
	BigInteger& operator++(); // Pre-incremento
	BigInteger operator++(int); // Post-incremento
	BigInteger& operator--(); // Pre-decremento
	BigInteger operator--(int); // Post-decremento

	friend std::ostream& operator<<(std::ostream&, const BigInteger&);
	friend std::istream& operator>>(std::istream&, BigInteger&);

	friend bool operator<(const BigInteger&, const BigInteger&);

	friend BigInteger operator+(const BigInteger&, const BigInteger&);
	friend BigInteger operator-(const BigInteger&, const BigInteger&);
	friend BigInteger operator*(const BigInteger&, const BigInteger&);
	friend BigInteger operator/(const BigInteger&, const BigInteger&);
	friend BigInteger operator%(const BigInteger&, const BigInteger&);

	// Métodos extra
	void RemoveZeros();
	
	friend BigInteger mcd(const BigInteger&, const BigInteger&);

 private:
	bool sign_; 			// 0 -> positivo | 1 -> negativo
	BigUnsigned n_; 
};

#endif



