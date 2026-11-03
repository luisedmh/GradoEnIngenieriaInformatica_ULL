/*
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Computabilidad y Algoritmia
* Curso: 2º
* Práctica 2: Cadenas y lenguajes
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 22/09/2024
* Archivo language.cc:
* Contiene la implementación de las funciones
* de la clase Language
* Referencias:
* Historial de Revisiones
*/

#include "language.h"

// Inicialización de la función insert
// Parámetros new_string del tipo std::string
// Ningún retorno (tipo void)
void Language::Insert(std::string new_string) {
  language_.insert(new_string);
}

// Sobrecarga del operador de salida
// Parámetros os y language del tipo ostream y Language respectivamente
std::ostream& operator<<(std::ostream& os, const Language& language) {
  os << '{';
  for (auto i = language.get_language().begin(); i != language.get_language().end(); i++) {
    os << *i;
    if (std::next(i) != language.get_language().end()) {
      os << ", ";
    }
  }
  os << '}';
  return os;
}