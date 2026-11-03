/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática* Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º
* Práctica 06: Implementación del TDA Árbol                                         
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 29/02/2025                                                                                                    
* Archivo nif.h:                                                                                                      
* Implementación de la clase nif                                                                           
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/  

#include "nif.h"

nif::nif(const long n) : n_(n) {}

nif::operator long() const { return n_; };

std::ostream& operator<<(std::ostream& os, const nif& n) {
  os << n.n_;
  return os;
}

std::istream& operator>>(std::istream& is, nif& n) {
  long tmp;
  is >> tmp;
  n = nif(tmp);
  return is;
}
