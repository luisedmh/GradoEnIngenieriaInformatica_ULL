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
* Archivo sub_tree.h:
* Declaración de la clase sub_tree dentro del namespace EMST
* Referencias:
* Historial de Revisiones:
*/

#pragma once

#include <iostream>
#include <cmath>

#include "point_types.h"

namespace EMST
{
	class sub_tree {
	 private:
		CyA::tree arcs_;
		CyA::point_collection points_;
		double cost_;

	 public:
		sub_tree(void);
		~sub_tree(void);

		void add_arc(const CyA::arc &a);
		void add_point(const CyA::point &p);
		bool contains(const CyA::point &p) const;
		void merge(const sub_tree &st, const CyA::weigthed_arc &a);

		inline const CyA::tree& get_arcs(void) const { return arcs_; }
		inline double get_cost(void) const { return cost_; }
	};

	typedef std::vector<sub_tree> sub_tree_vector;
}