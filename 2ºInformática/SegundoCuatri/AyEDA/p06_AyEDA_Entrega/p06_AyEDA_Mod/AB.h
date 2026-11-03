/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática* Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º
* Práctica 06: Implementación del TDA Árbol                                         
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 29/02/2025                                                                                                    
* Archivo AB.h:                                                                                                      
* Declaración e implementación de la clase AB                                                                            
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/  

#ifndef AB_H
#define AB_H

#include "NodoB.h"

#include <iostream>
#include <queue>
#include <utility>

template <class Key> class AB;
template <class Key> std::ostream& operator<<(std::ostream&, const AB<Key>&);

template <class Key>
class AB {
 public:
	virtual bool insertar(const Key&) = 0;
	virtual void insertar_traza(const Key&) = 0;  
	virtual bool buscar(const Key&) const = 0;
	void inorden() const;
	void recorrer_recursivo(NodoB<Key>*) const;
	void imprimirPorNiveles(std::ostream& os) const;
 protected:
	NodoB<Key>* raiz_;
};

template<class key>
void AB<key>::inorden() const {
	recorrer_recursivo(raiz_);
  std::cout << std::endl;
}

template<class key>
void AB<key>::recorrer_recursivo(NodoB<key>* nodo) const {
	if (nodo == nullptr) {
		return;
	} else {
		recorrer_recursivo(nodo->izdo());
		std::cout << nodo->dato() << ' ';
		recorrer_recursivo(nodo->dcho());
	}
}

template <class key>
std::ostream& operator<<(std::ostream& os, const AB<key>& arbol) {
	arbol.imprimirPorNiveles(os);
	return os;
}

template <class key>
void AB<key>::imprimirPorNiveles(std::ostream& os) const {
	//std::cerr << "hola" << std::endl;
	std::queue<std::pair<NodoB<key>*, int>> cola;
	cola.push({raiz_, 0});
	int nivel_actual = 0;

	os << "Nivel " << nivel_actual << ": ";
	while (!cola.empty()) {
		auto [nodo, nivel] = cola.front();
		cola.pop();
		if (nivel > nivel_actual) {
			nivel_actual = nivel;
			os << "\nNivel " << nivel_actual << ": ";
		}
		if (nodo != nullptr) {
			//std::cerr << "hola" << std::endl;
			os << "[" << nodo->dato() << "] ";
			cola.push({nodo->izdo(), nivel + 1});
			cola.push({nodo->dcho(), nivel + 1});
		} else {
			os << "[.] ";
		}
	}
}

#endif