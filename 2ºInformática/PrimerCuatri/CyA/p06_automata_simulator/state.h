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
* Archivo state.h:
* Declaración de la clase State que se encargará de generar
* un objeto con las funcionalidades de un estado
* para definir el objeto cadena
* Referencias:
* Historial de Revisiones
*/

#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <map>
#include <set>

class State {
 public:
// Constructores
	// Constructor por defecto
  State();
	// Constructor a partir de parámetros
 	State(int id, bool final_state);
// Métodos
	// Getters
		// Getter para el id
 	int get_id();
		// Geter para si es de aceptación o no
	bool get_state_final();
		// Getter para las transiciones del estado
	const std::multimap<char, int>& get_transitions() const;
	// Método que añade transiciones a un estado
	void addTransition(char symbol, int destination);
	// Método que obtiene el conjunto de estados siguientes a partir de un símbolo
	std::set<int> get_next_states(char symbol) const;
 private:
	int id_;
	bool final_state_;
	std::multimap<char, int> transitions_;
};
#endif