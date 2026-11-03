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
* Archivo point_types.cc:
* Implementación de las sobrecargas de salida del namespace CyA
* Referencias:
* Historial de Revisiones:
*/

#include "point_types.h"

#include <iomanip>

/**
 * @brief Sobrecarga del operador de salida para un point_vector
 * @param os ostream
 * @param ps point_vector
 * @return Ninguno
 */
std::ostream& operator<<(std::ostream& os, const CyA::point_vector& ps) {
	os << ps.size() << std::endl;
	for (const CyA::point &p : ps) {
		os << p << std::endl;
	}
	return os;
}

/**
 * @brief Sobrecarga del operador de salida para un point
 * @param os ostream
 * @param p point
 * @return Ninguno
 */
std::ostream& operator<<(std::ostream& os, const CyA::point& p) {
	os << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC) << p.first << "\t" << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC) << p.second;
	return os;
}

/**
 * @brief Sobrecarga del operador de entrada para un point_vector
 * @param is istream
 * @param ps point_vector
 * @return Ninguno
 */
std::istream& operator>>(std::istream& is, CyA::point_vector& ps) {
	int n;
	is >> n;
	ps.clear();
	for (int i = 0; i < n; ++i) {
		CyA::point p;
		is >> p;
		ps.push_back(p);
	}
	return is;
}

/**
 * @brief Sobrecarga del operador de entrada para un point
 * @param is istream
 * @param p point
 * @return Ninguno
 */
std::istream& operator>>(std::istream& is, CyA::point& p) {
	is >> p.first >> p.second;
	return is;
}