/*
* Universidad de La Laguna
* Escuela Superior de Ingenierí y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Computabilidad y Algoritmia
* Curso: 2º
* Práctica 2: Cadenas y lenguajes
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 22/09/2024
* Archivo language.h:
* Contiene la declaración de la clase language
* para definir el objeto cadena
* Referencias:
* Historial de Revisiones
*/

#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <fstream>
#include <cstdlib> 
#include <iostream>
#include <string>
#include <set>

class String;

class Language {
 public:
// Constructor por defecto
	Language() : language_() {}
// Métodos
	// Getter
	const std::set<std::string>& get_language() const {return language_;}
	void Insert(std::string new_string);
 private:
	std::set<std::string> language_;
};  

// Sobrecarga de operadores
std::ostream& operator<<(std::ostream& os, const Language& language);


#endif