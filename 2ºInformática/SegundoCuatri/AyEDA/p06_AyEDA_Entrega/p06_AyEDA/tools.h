/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática* Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º
* Práctica 06: Implementación del TDA Árbol                                         
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 29/02/2025                                                                                                    
* Archivo tools.h:                                                                                                      
* Declaración de las funciones auxiliares para el programa principal                                                                      
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/  


#pragma once

#include <string>
#include <vector>
#include <fstream>
#include "AB.h"
#include "nif.h"

struct args {
  bool help = false;
  bool trace = false;
  bool init;
  bool AVL;
  long size = 0;
  std::string file = "";
};

void help();
void menu();
void make_tree(AB<nif>*&, std::vector<nif>, bool, bool);
args parse_args(int, char**);
std::vector<nif> read_input(bool, const long, const std::string&);
