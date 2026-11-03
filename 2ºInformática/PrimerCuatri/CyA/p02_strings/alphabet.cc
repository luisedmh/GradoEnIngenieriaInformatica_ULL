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
* Archivo alphabet.cc:
* Implementación de las funciones de la clase
* Alphabet que se encargará de generar
* un objeto con las funcionalidades de un alfabeto
* para definir el objeto cadena
* Referencias:
* Historial de Revisiones
*/

#include "alphabet.h"

// Inicialización del constructor alphabet
// 1 parámetro de entrada symbols de tipo string
Alphabet::Alphabet(const std::string& symbols) {
  for (const char& symbol : symbols) {
    alphabet_.insert(symbol);
  }
}

// Sobrecarga del operador de entrada
// Parámetros is y alphabet de tipo istream y Alphabet respectivamente
std::istream& operator>>(std::istream& is, Alphabet& alphabet) {
  std::string insymbols;
  is >> insymbols;
  alphabet = Alphabet(insymbols);
  return is;
}

// Sobrecarga del operador de salida
// Parámetros os y alphabet de tipo ostream y Alphabet respectivamente
std::ostream& operator<<(std::ostream& os, const Alphabet& alphabet) {
  os << '{';
  for (auto i = alphabet.get_alphabet().begin(); i != alphabet.get_alphabet().end(); i++) {
    os << *i;
    if (std::next(i) != alphabet.get_alphabet().end()) {
      os << ", ";
    }
  }
  os << '}';
  return os;
}
