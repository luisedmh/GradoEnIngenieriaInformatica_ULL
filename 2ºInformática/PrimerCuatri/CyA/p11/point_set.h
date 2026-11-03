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
* Archivo point_set.h:
* Declaración de la clase point_set
* Referencias:
* Historial de Revisiones:
*/

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "point_types.h"
#include "sub_tree.h"

#pragma once

typedef std::vector<EMST::sub_tree> forest;

class point_set : public CyA::point_vector {
 private:
	CyA::tree emst_;

 public:
	point_set(const CyA::point_vector &points);
	~point_set(void);

	void EMST(void);

	void write_tree(std::ostream &os, const CyA::point_vector &points) const;
	void write(std::ostream &os) const;

	inline const CyA::tree& get_tree(void) const { return emst_; }
	inline const CyA::point_vector& get_points(void) const { return *this; }
	inline const double get_cost(void) const { return compute_cost(); }

 private:
	void compute_arc_vector(CyA::arc_vector &av) const;
	void find_incident_subtrees(const forest& st, const CyA::arc &a, int& i, int& j) const;
	void merge_subtrees(forest& st, const CyA::arc &a, int i, int j) const;
	int max_degree(const CyA::point_vector &points) const;

	double compute_cost(void) const;

	double euclidean_distance(const CyA::arc& a) const;
};