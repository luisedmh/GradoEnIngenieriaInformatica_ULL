/**
* Universidad de La Laguna
* Escuela Superior de Ingenierí y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Computabilidad y Algoritmia
* Curso: 2º
* Práctica 8: Gramáticas en Forma Normal de Chomsky
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 04/11/2024
* Archivo alphabet.h:
* Declaración de la clase Alphabet que se encargará de generar
* un objeto con las funcionalidades de un alfabeto
* para definir el objeto cadena
* Referencias:
* Historial de Revisiones
*/

#ifndef ALPHABET_H
#define ALPHABET_H

#include <fstream>
#include <cstdlib> 
#include <iostream>
#include <string>
#include <set>

typedef char Symbol;

class Alphabet {
 public:
// Constructores
	// Constructor por defecto
	Alphabet() = default;
	// Constructor a partir de un parámetro
	Alphabet(const std::string& alphabet);
// Métodos
	void AddSymbol(const char symbol);
	// Getter
  const std::set<Symbol>& get_alphabet() const {return alphabet_;}
 private:
	std::set<Symbol> alphabet_;
};

#endif