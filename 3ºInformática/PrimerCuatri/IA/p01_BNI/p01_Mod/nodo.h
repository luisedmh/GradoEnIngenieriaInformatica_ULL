/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Inteligencia Artificial
* Curso: 3º Práctica 01: Búsquedas no informadas
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 01/10/2025
* Archivo nodo.h:                                                                                               
* Declaración de la clase Nodo
* Referencias:
* Historial de Revisiones:
*/

#ifndef NODO_H
#define NODO_H

#include <iostream>

class Nodo {
 public:
	// Constructor
	Nodo(int estado, int i = -1) : estado_(estado), indice_padre_(i) {}
	// Nodo(int estado, int i = -1, float coste_acumulado = 0.0) : estado_(estado), indice_padre_(i), coste_acumulado_(coste_acumulado) {}

	// Getters
	int getEstado() const { return estado_; }
	int getIPadre() const { return indice_padre_; }
	// float getCoste() const { return coste_acumulado_;}
	
 private:
	int estado_;
	int indice_padre_;
	// float coste_acumulado_;
};

#endif