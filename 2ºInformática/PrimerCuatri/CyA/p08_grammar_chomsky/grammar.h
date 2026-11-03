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
* Archivo grammar.h:
* Declaración de la clase Grammar que se encargará de generar
* un objeto con las funcionalidades de una gramática
* para definir el objeto cadena
* Referencias:
* Historial de Revisiones
*/

#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cstdlib>

#include "alphabet.h"
#include "not_terminal.h"



class Grammar {
 public:
// Constructores
	// Por defecto
	Grammar() : alphabet_(), not_terminal_(), productions_(), start_not_terminal_('S') {}
	// A partir de entrada
	Grammar(std::istream& input_file);
// Métodos
	void Transform_CNF();
	void Output_grammar(std::ostream& output_file);
	bool Check_Equal(Grammar grammar_input);
	// Getters
	const Alphabet& get_first_alphabet() {return alphabet_;}
	const NotTerminal& get_not_terminal() {return not_terminal_;}
	const std::multimap<char, std::string>& get_productions() {return productions_;}
 private:
	Alphabet alphabet_;
	NotTerminal not_terminal_;
	std::multimap<char, std::string> productions_;
	char start_not_terminal_;
};

#endif