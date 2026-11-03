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
* Archivo state.cc:
* Inicialización de la clase State que se encargará de generar
* un objeto con las funcionalidades de un estado
* para definir el objeto cadena
* Referencias:
* Historial de Revisiones
*/

#include "state.h"
/**
 * @brief Constructor a partir de parámetros de la clase State
 * @param id número que identifica al estado
 * @param final_state variable booleana que dice si es un estado de aceptación o no
 * @return Ninguno, crea el objeto
 */
State::State(int id, bool final_state) : id_(id), final_state_(final_state) {}

/**
 * @brief Método que añade las transiciones de un estado
 * @param symbol Char que señala el posible símbolo de entrada
 * @param destination Int que dirige el destino de dicho símbolo en ese estado
 * @return Ninguno, es un void
 */
void State::addTransition(char symbol, int destination) {
  transitions_.insert({symbol, destination});
}

/**
 * @brief Método que a partir de un estado y un símbolo devuelve el conjunto de estados destinos
 * @param symbol Char del símbolo de entrada
 * @return Conjunto de estados destinos
 */
std::set<int> State::get_next_states(char symbol) const {
  std::set<int> result;
  auto range = transitions_.equal_range(symbol);
  for (auto it = range.first; it != range.second; ++it) {
    result.insert(it->second);
  }
  return result;
}

/**
 * @brief Getter que devielve el identificador del estado
 * @return Int que indica el estado
 */
int State::get_id() {
	return id_;
}

/**
 * @brief Getter que devielve si el estado es de aceptación o no
 * @return Bool que indica lo anterior
 */
bool State::get_state_final() {
	return final_state_;
}

/**
 * @brief Getter que devuelve las transiciones de un estado
 * @return multimap de char e int que indica las transiciones desde un estado
 */
const std::multimap<char, int>& State::get_transitions() const {
	return transitions_;
}