/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Inteligencia Artificial
* Curso: 3º Práctica 01: Búsquedas no informadas
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 01/10/2025
* Archivo grafo.cc:                                                                                               
* Declaración de la clase Grafo
* Referencias:
* Historial de Revisiones:
*/

#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <vector>
#include <fstream>
#include "tools.h"
#include "nodo.h"

class Grafo {
 public:
	// Constructor
	Grafo(const std::string& nombre_archivo, const int origen, const int destino);

	// Métodos para imprimir resultados
	void ImprimirGrafo(std::ostream& os = std::cout);
	void ImprimirParcial(const Resultado& resultado, std::ostream& os = std::cout);
	void ImprimirResultado(const std::vector<Nodo>& generados, const Nodo* nodo_final, std::ostream& os = std::cout);

	// Método para trackear estados repetidos en la misma rama
	bool EstadoRepetido(const std::vector<Nodo>& generados, Nodo* actual, int estado);

	// Métodos para realizar las búsquedas no informadas
	void BNI(const std::string& modo_busqueda, std::ostream& os = std::cout);
	void DFS(std::ostream& os = std::cout);
	void BFS(std::ostream& os = std::cout);
	
 private:
	std::vector<std::vector<float>> grafo_;
	int num_vertices_;
	int num_aristas_;
	int estado_origen_;
	int estado_destino_;
};

#endif