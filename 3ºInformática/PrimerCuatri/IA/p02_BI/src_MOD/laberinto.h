/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Inteligencia Artificial
* Curso: 3º Práctica 02: Búsquedas informadas
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 14/10/2025
* Archivo laberinto.h:                                                                                               
* Declaración de la clase Laberinto
* Referencias:
* Historial de Revisiones:
*/


#ifndef LABERINTO_H
#define LABERINTO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <cmath>

#include "nodo.h"
#include "tools.h"

class Laberinto {
 public:
	// Constructor
	Laberinto(const std::string& input_file);
	// Métodos de impresión
	void ImprimirLaberinto(std::ostream& os = std::cout);
	Nodo ImprimirCamino(const std::vector<Nodo>& inspeccionados, int aux, Datos& datos, std::ostream& os = std::cout);
	void ImprimirCaminoFinal(const std::vector<Nodo>& inspeccionados, int aux, Datos& datos, std::ostream& os = std::cout);

	// Heurísticas
	int CalcularCosteEstimado(const Nodo& nodo);
	int CalcularCosteEstimadoEuclidiano(const Nodo& nodo);
	// Método que resuelve A*
	Nodo ResolverEstatico(Datos& datos, std::ostream& os = std::cout);

	// Comportamiento dinámico del laberinto
	void MezclarLaberinto();
	// Resolución del laberinto dinámico
	void ResolverDinamico(std::ostream& os = std::cout);

	void setInicio(int i, int j) {
		//laberinto_[inicio_.first][inicio_.second] = '0';
		inicio_.first = i;
		inicio_.second = j;
		//laberinto_[i][j] = '3';
	}

 private:
	std::vector<std::vector<char>> laberinto_;
	std::pair<int, int> inicio_;
	std::pair<int, int> fin_;
	int filas_;
	int columnas_;
	int num_paredes_;
};

#endif