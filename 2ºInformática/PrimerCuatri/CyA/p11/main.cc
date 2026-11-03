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
* Archivo main.cc:
* Implementación de la función main
* Referencias:
* Historial de Revisiones:
*/

#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include <cmath>
#include <fstream>
#include <string>

#include "point_set.h"
#include "point_types.h"
#include "sub_tree.h"
#include "tools.h"

/**
 * @brief Función main, principal del programa
 * @param argc número de parámetros de entrada por terminal
 * @param argv parámetros de entrada por terminal
 * @return Int, determina el estado de la finalización del programa
 */

int main(int argc, char* argv[]) {
	bool d_option = false;

	if (!Usage(argc, argv, d_option)) {
		return 1;
	}

	CyA::point_vector points;
	std::cin >> points;

	point_set ps(points);

	ps.EMST();

	ps.write_tree(std::cout, points);

	if (d_option) {
		std::string d_option_filename = std::string(argv[2]);
		std::ofstream d_option_stream(d_option_filename);
		if (!d_option_stream) {
			std::cerr << "Error: No se pudo abrir el archivo " << d_option_filename << " para escritura." << std::endl;
			return 1;
		}

		d_option_stream << "graph {" << std::endl;

		for (const auto& point : ps.get_points()) {
			d_option_stream << "  \"" << point.first << "," << point.second 
											<< "\" [pos=\"" << point.first << "," << point.second << "!\"];" << std::endl;
		}

		for (const auto& arc : ps.get_tree()) {
			const auto& start = arc.first;
			const auto& end = arc.second;
			d_option_stream << "  \"" << start.first << "," << start.second << "\" -- \"" 
											<< end.first << "," << end.second << "\";" << std::endl;
		}

		d_option_stream << "}" << std::endl;
		std::cout << "Archivo DOT generado: " << d_option_filename << std::endl;
	}

	return 0;
}