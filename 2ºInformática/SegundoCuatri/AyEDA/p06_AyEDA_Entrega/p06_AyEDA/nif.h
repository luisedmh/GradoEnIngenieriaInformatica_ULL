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
* Declaración de la clase nif                                                                           
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/  

#ifndef NIF_H
#define NIF_H

#include <iostream>
#include <cstdlib>

class nif {
 public:
  nif(const long n = 10000000 + rand() % 90000000);
  operator long() const;
  friend std::ostream& operator<<(std::ostream& os, const nif& n);
  friend std::istream& operator>>(std::istream& is, nif& n);
 private:
  long n_;
};

#endif