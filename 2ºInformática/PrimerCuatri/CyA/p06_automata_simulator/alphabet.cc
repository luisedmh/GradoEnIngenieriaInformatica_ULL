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
