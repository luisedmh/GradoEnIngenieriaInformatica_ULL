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
* Archivo sub_tree.cc:
* Implementación de los métodos de la clase sub_tree dentro del namespace EMST
* Referencias:
* Historial de Revisiones:
*/

#include <iomanip>
#include <cmath>

#include <algorithm>
#include <utility>

#include "sub_tree.h"

namespace EMST {

	/**
	 * @brief Constructor por defecto
	 * @return Ninguno, crea un objeto
	 */
	sub_tree::sub_tree(void) : arcs_(), points_(), cost_(0)	{}

	/**
	 * @brief Destructor
	 * @return Ninguno, destruye un objeto
	 */
	sub_tree::~sub_tree(void) {}

	/**
	 * @brief Método add_arc que añade un arco al sub_tree
	 * @param a arc
	 * @return Ninguno
	 */
	void sub_tree::add_arc(const CyA::arc &a) {
		arcs_.push_back(a);
		points_.insert(a.first);
		points_.insert(a.second);
	}

	/**
	 * @brief Método add_point que añade un punto al sub_tree
	 * @param p point
	 * @return Ninguno
	 */
	void sub_tree::add_point(const CyA::point &p) {
		points_.insert(p);
	}

	/**
	 * @brief Método contains que comprueba si un punto pertence a un sub_tree
	 * @param p point
	 * @return bool, verdadero si lo contiene
	 */
	bool sub_tree::contains(const CyA::point &p) const {
		return points_.find(p) != points_.end();
	}

	/**
	 * @brief Método merge que combina dos subarboles en uno solo
	 * @param st sub_tree
	 * @param a weigthed_arc
	 * @return Ninguno
	 */
	void sub_tree::merge(const sub_tree &st, const CyA::weigthed_arc &a) {
		arcs_.insert(arcs_.end(), st.arcs_.begin(), st.arcs_.end());
		arcs_.push_back(a.second);

		points_.insert(st.points_.begin(), st.points_.end());

		cost_ += a.first + st.get_cost();
	}
}