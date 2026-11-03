/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática* Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º
* Práctica 06: Implementación del TDA Árbol                                         
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 29/02/2025                                                                                                    
* Archivo ABB.h:                                                                                                      
* Declaración e implementación de la clase ABB                                                                          
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/  

#ifndef ABB_H
#define ABB_H

#include "AB.h"

template <class Key>
class ABB : public AB<Key> {
 public:
  ABB() {this->raiz_ = nullptr;}
  bool insertar(const Key&) override;
  void insertar_traza(const Key&) override;
  bool buscar(const Key&) const override;
 private:
  bool insertar_recursivo(NodoB<Key>*&, const Key&);
};

template <class Key>
void ABB<Key>::insertar_traza(const Key& k) {
  return;
}

template <class Key>
bool ABB<Key>::insertar(const Key& k) {
	return insertar_recursivo(this->raiz_, k);
}

template <class Key>
bool ABB<Key>::insertar_recursivo(NodoB<Key>*& nodo, const Key& k) {
	if (nodo == nullptr) { 
		nodo = new NodoB<Key>(k); return true; 
	} else if (k < nodo->dato()) {
		return insertar_recursivo(nodo->izdo(), k);
	} else 
	if (k > nodo->dato()) {
		return insertar_recursivo(nodo->dcho(), k);
	} else {
		return false;
	}
}

template <class Key>
bool ABB<Key>::buscar(const Key& k) const {
	return buscar_recursivo(this->raiz_, k) != nullptr;
}

template <class Key>
NodoB<Key>* buscar_recursivo(NodoB<Key>* nodo, const Key& k) {
  if (nodo == nullptr) {
		return nullptr;
	}
  if (k == nodo->dato()) {
		return nodo;
	}
  if (k < nodo->dato()) {
		return buscar_recursivo(nodo->izdo(), k);
	} else {
		return buscar_recursivo(nodo->dcho(), k);
	}
}

#endif