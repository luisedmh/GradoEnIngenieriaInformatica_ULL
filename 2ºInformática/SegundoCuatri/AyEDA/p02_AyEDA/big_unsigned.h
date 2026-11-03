/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática* Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º* Práctica 01: Representación de números grandes                                          
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 11/02/2025                                                                                                    
* Archivo big_unsigned.h:                                                                                                      
* Declaración de la clase BigUnsigned                                                                                  
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/   

#ifndef BIGUNSIGNED_H
#define BIGUNSIGNED_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <cstring>

class BigUnsigned {
 public:
	BigUnsigned(unsigned n = 0);
	BigUnsigned(const std::string&);
	BigUnsigned(const BigUnsigned&);
	BigUnsigned(const std::vector<unsigned char>&);

	BigUnsigned& operator=(const BigUnsigned&);
	bool operator==(const BigUnsigned&) const;
	BigUnsigned& operator++(); // Pre-incremento
	BigUnsigned operator++(int); // Post-incremento
	BigUnsigned& operator--(); // Pre-decremento
	BigUnsigned operator--(int); // Post-decremento

	friend std::ostream& operator<<(std::ostream&, const BigUnsigned&);
	friend std::istream& operator>>(std::istream&, BigUnsigned&);

	friend bool operator<(const BigUnsigned&, const BigUnsigned&);
	friend bool operator>(const BigUnsigned&, const BigUnsigned&);

	friend BigUnsigned operator+(const BigUnsigned&, const BigUnsigned&);
	friend BigUnsigned operator-(const BigUnsigned&, const BigUnsigned&);
	friend BigUnsigned operator*(const BigUnsigned&, const BigUnsigned&);
	friend BigUnsigned operator/(const BigUnsigned&, const BigUnsigned&);
	friend BigUnsigned operator%(const BigUnsigned&, const BigUnsigned&);

	// Métodos extra
	void RemoveZeros();	

 private:
	std::vector<unsigned char> n_;
};





/*
* mcd(a,b) = mcd(b, a % b); Hacer de manera iterativa
*/

#endif