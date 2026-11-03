/**
* Universidad de La Laguna
* Escuela Superior de Ingenierí y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Computabilidad y Algoritmia
* Curso: 2º
* Práctica 6: Diseño y simulación de autómatas finitos
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 20/10/2024
* Archivo automaton.h:
* Declaración de la clase Automaton que se encargará de generar
* un objeto con las funcionalidades de un autómata finito
* para definir el objeto cadena
* Referencias:
* Historial de Revisiones
*/

#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <map>
#include <iostream>
#include <vector>
#include <sstream>

#include "alphabet.h"
#include "state.h"

class Automaton {
 public:
// Constructores
	// Constructor por defecto
	Automaton();
// Métodos
	// Método que se encarga de la entrada del autómata
	bool LoadFromFile(const std::string& filename);
	// Método que se determina si un símbolo pertenece al alfabeto
	bool BelongsAlphabet(const char symbol) const;
	// Método que se determina si un estado pertenece al autómata
	bool BelongsState(const int dest) const;
	// Método que comprueba si una entrada forma parte del lenguaje
	bool Simulate(const std::string& input);
	// Método encargado de la sálida del programa
	void FinalOutput(const std::string& input_filename);
	// Método que devuelve si un estado es de aceptación o no
	bool IsFinal(const std::set<int>& current_states);
	// Método que realiza la ε-clausura
	std::set<int> EpsilonClosure(const std::set<int>& current_states) const;
 private:
	int num_states_;
	int initial_state_;
  Alphabet alphabet_;
  std::vector<State> states_;
};

#endif