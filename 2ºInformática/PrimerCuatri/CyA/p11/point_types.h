/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Computabilidad y Algoritmia
* Curso: 2º
* Práctica 11: Algoritmos Voraces (Greedy). Euclidean Minimum Spanning Tree
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 10/12/2024
* Archivo point_types.h:
* Declaración del namespace CyA
* Referencias:
* Historial de Revisiones:
*/

#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <set>

#define MAX_SZ 3
#define MAX_PREC 0

namespace CyA {
	typedef std::pair<double, double> point;

	typedef std::pair<point, point> line;
	typedef std::vector<point> point_vector;

	typedef std::pair<point, point> arc;
	typedef std::pair<double, arc> weigthed_arc;
	typedef std::vector<weigthed_arc> arc_vector;

	typedef std::set<point> point_collection;

	typedef std::vector<arc> tree;
}

std::ostream& operator<<(std::ostream& os, const CyA::point_vector& ps);
std::ostream& operator<<(std::ostream& os, const CyA::point& ps);

std::istream& operator>>(std::istream& is, CyA::point_vector& ps);
std::istream& operator>>(std::istream& is, CyA::point& ps);