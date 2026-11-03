/*
* Universidad de La Laguna
* Escuela Superior de Ingenierí y Tecnología
* Grado en Ingenier´ıa Inform´atica
* Asignatura: Computabilidad y Algoritmia
* Curso: 2º
* Práctica 2: Cadenas y lenguajes
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 22/09/2024
* Archivo string.h:
* Contiene la declaración de la clase string
* para definir el objeto cadena
* Referencias:
* Historial de Revisiones
*/

#ifndef STRING_H
#define STRING_H

#include <fstream>
#include <cstdlib> 
#include <iostream>
#include <string>
#include <set>

#include "language.h"

class Language;

class String {
 public:
// Constructores
	// Constructor por defecto
	String() = default;
	// Constructor a partir de parámetro
	String(const std::string instring) : string_(instring) {}
// Métodos
	// Getter
	std::string get_string() const {return string_;}
	// Método set_string
	void set_string(const std::string string) {string_ = string;}
	// Método Lenght
	int Lenght() const;
	// Método Reverse
	String Reverse();
	// Método Get_Prefixes
	Language Get_Prefixes();
	// Método Get_Suffixes
	Language Get_Suffixes();

	// MODIFICACION
	// Método de la potencia
	String Pow(const int n);
 private:
	std::string string_;
};

// Sobrecarga de operadores
	// Operador de entrada
std::istream& operator>>(std::istream& is, String& instring);
	// Operador de salida
std::ostream& operator<<(std::ostream& os, String& instring);


#endif