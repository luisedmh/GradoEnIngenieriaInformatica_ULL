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
* Archivo point_set.cc:
* Implementación de los métodos de la clase point_set
* Referencias:
* Historial de Revisiones:
*/

#include "point_set.h"

/**
 * @brief Constructor por parámetro de point_set
 * @param points vector de puntos
 * @return Ninguno, crea un objeto
 */
point_set::point_set(const CyA::point_vector &points) : CyA::point_vector(points), emst_() {}

/**
 * @brief Destructor de point_set
 * @return Ninguno, destruye un objeto
 */
point_set::~point_set(void) {}

/**
 * @brief Método EMST que aplica kruskal
 * @return Ninguno
 */
void point_set::EMST(void) {
	CyA::arc_vector av;
	compute_arc_vector(av);

	EMST::sub_tree_vector stv;

	for (const CyA::point &p : *this) {
		EMST::sub_tree st;
		st.add_point(p);
		stv.push_back(st);
	}

	for (const CyA::weigthed_arc &a : av) {
		int i, j;
		find_incident_subtrees(stv, a.second, i, j);

		if (i != j) {
			merge_subtrees(stv, a.second, i, j);
		}
	}

	emst_ = stv[0].get_arcs(); // El resultado es el EMST
}

/**
 * @brief Método write_tree que genera la salida del árbol generador mínimo
 * @param os ostream
 * @return Ninguno
 */
void point_set::write_tree(std::ostream& os, const CyA::point_vector &points) const {
	os << "Árbol Generador Mínimo Euclidiano (EMST):" << std::endl;
	int max = max_degree(points);
	for (const auto& arc : emst_) {
		os << "(" << arc.first.first << ", " << arc.first.second << ") -- ";
		os << "(" << arc.second.first << ", " << arc.second.second << ")" << std::endl;
	}
	std::cout << "El grado máximo del árbol es: " << max << std::endl;
}

/**
 * @brief Método write escribe los puntos
 * @param os ostream
 * @return Ninguno
 */
void point_set::write(std::ostream& os) const {
	os << "Conjunto de Puntos:\n";
	for (const auto& point : *this) {
		os << "(" << point.first << ", " << point.second << ")\n";
	}
}

/**
 * @brief Método compute_arc_vector que calcula todas las posibles aristas y las ordena por peso
 * @param av arc_vector
 * @return Ninguno
 */
void point_set::compute_arc_vector(CyA::arc_vector &av) const {
	av.clear();
	const int n = size();

	for (int i = 0; i < n - 1; ++i) {
		const CyA::point &point_i = (*this)[i];
		for (int j = i + 1; j < n; ++j) {
			const CyA::point &point_j = (*this)[j];
			const double dist = euclidean_distance(std::make_pair(point_i, point_j));
			av.push_back(std::make_pair(dist, std::make_pair(point_i, point_j)));
		}
	}
	std::sort(av.begin(), av.end());
}

/**
 * @brief Método find_inciden_subtrees que identifica en qué subárboles se encuentran los puntos que forman la arista
 * @param stv vector de subtrees
 * @param a arc
 * @param i índice
 * @param j índice
 * @return Ninguno
 */
void point_set::find_incident_subtrees(const EMST::sub_tree_vector &stv, const CyA::arc &a, int &i, int &j) const {
	i = j = -1;
	for (int k = 0; k < stv.size(); ++k) {
		if (stv[k].contains(a.first)) {
			i = k;
		}
		if (stv[k].contains(a.second)) {
			j = k;
		}
		if (i != -1 && j != -1) {
			break;
		}
	}
}

/**
 * @brief Método merge_subtrees que combina dos subarboles a partir de una arista a
 * @param stv vector de subtrees
 * @param a arc
 * @param i índice
 * @param j índice
 * @return Ninguno
 */
void point_set::merge_subtrees(EMST::sub_tree_vector &stv, const CyA::arc &a, int i, int j) const {
	stv[i].merge(stv[j], std::make_pair(euclidean_distance(a), a));
	stv.erase(stv.begin() + j); 
}

/**
 * @brief Método compute_cost que calcula el costo total del árbol generador mínimo
 * @return cost de tipo double
 */
double point_set::compute_cost(void) const {
	double total_cost = 0;
	for (const CyA::arc &a : emst_) {
		total_cost += euclidean_distance(a);
	}
	return total_cost;
}

/**
 * @brief Método euclidean_distance que calcula la distancia entre dos puntos
 * @return double que representa la distancia
 */
double point_set::euclidean_distance(const CyA::arc &a) const
{
	const double distance_x = a.first.first - a.second.first;
	const double distance_y = a.first.second - a.second.second;
	return std::sqrt(distance_x * distance_x + distance_y * distance_y);
}


// MODIFICACIÓN

int point_set::max_degree(const CyA::point_vector &points) const {
	int max = 0;
	for (const auto& p : points) {
		int amount_p = 0;
		for (const auto& a : emst_) {
			if 	(p == a.first || p == a.second) {
				amount_p += 1;
			}
		}
		if (amount_p >= max) {
			max = amount_p;
		}
	}
	return max;
}