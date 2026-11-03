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
* Archivo not-terminal.h:
* Declaración de la clase NotTerminal que se encargará de generar
* un objeto con las funcionalidades de los símbolos no terminales
* para definir el objeto cadena
* Referencias:
* Historial de Revisiones
*/

#ifndef NOTTERMINAL_H
#define NOTTERMINAL_H

#include <fstream>
#include <cstdlib> 
#include <iostream>
#include <string>
#include <set>

class NotTerminal {
 public:
// Constructor por defecto
	NotTerminal() = default;
// Métodos
	void AddNotTerminal(const char not_terminal);
	// getter
	const std::set<char>& get_not_terminal() const {return not_terminal_;}
 private:
	std::set<char> not_terminal_; 
};
#endif