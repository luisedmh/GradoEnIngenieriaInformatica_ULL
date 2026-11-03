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
* Archivo alphabet.cc:
* Implementación de las funciones de la clase
* Alphabet que se encargará de generar
* un objeto con las funcionalidades de un alfabeto
* para definir el objeto cadena
* Referencias:
* Historial de Revisiones
*/

#include "alphabet.h"

/**
 * @brief Constructor de la clase alphabet
 * @param symbols String que indica todos los símbolos del alfabeto
 * @return Ninguno, crea el objeto
 */

Alphabet::Alphabet(const std::string& symbols) {
  for (const char& symbol : symbols) {
    alphabet_.insert(symbol);
  }
}

/**
 * @brief Método que añade un símbolo al alfabeto
 * @param symbol Char del símbolo a añadir
 * @return Ninguno
 */
void Alphabet::AddSymbol(const char symbol) {
	alphabet_.insert(symbol);
}
