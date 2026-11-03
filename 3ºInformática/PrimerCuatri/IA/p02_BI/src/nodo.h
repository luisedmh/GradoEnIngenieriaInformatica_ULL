/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Inteligencia Artificial
* Curso: 3º Práctica 02: Búsquedas informadas
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 14/10/2025
* Archivo nodo.h:                                                                                               
* Declaración de la clase Nodo
* Referencias:
* Historial de Revisiones:
*/

#ifndef NODO_H
#define NODO_H

#include <iostream>
#include <limits>

const int INFINITO = std::numeric_limits<int>::max();

class Nodo {
 public:
	// Constructor
	//Nodo(int estado, int i = -1) : estado_(estado), indice_padre_(i) {}
	Nodo(int pos_i = -1, int pos_j = -1, int i = -1,int coste_acumulado = 0, int coste_total_estimado = INFINITO) : pos_({pos_i, pos_j}), indice_padre_(i), coste_acumulado_(coste_acumulado), coste_total_estimado_(coste_total_estimado) {}

	// Getters
	std::pair<int, int> getPos() const { return pos_;}
	int getIPadre() const { return indice_padre_;}
	int getCosteEstimado() const { return coste_total_estimado_;}
	int getCosteAcumulado() const {return coste_acumulado_;}

	// Setters
	void setIPadre(int i) { indice_padre_ = i;}
	void setCosteEstimado(int coste) {coste_total_estimado_ = coste;}
	void setCosteAcumulado(int coste) { coste_acumulado_ = coste;}
	
 private:
	std::pair<int, int> pos_;
	int indice_padre_;
	int coste_total_estimado_;
	int coste_acumulado_;
};

#endif