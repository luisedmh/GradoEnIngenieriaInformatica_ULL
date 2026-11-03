/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática* Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º
* Práctica 06: Implementación del TDA Árbol                                         
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 29/02/2025                                                                                                    
* Archivo ABE.h:                                                                                                      
* Declaración e implementación de la clase ABE                                                                            
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/  

#ifndef ABE_H
#define ABE_H

#include "AB.h"
#include "NodoAVL.h"

template <class Key>
class ABE : public AB<Key> {
 public:
  ABE() {this->raiz_ = nullptr;}
  bool insertar(const Key&) override;
  void insertar_traza(const Key&) override;
  bool buscar(const Key&) const override;
 private:
  bool insertar_recursivo(NodoAVL<Key>*&, const Key&);
};

template <class Key>
void ABE<Key>::insertar_traza(const Key& k) {
  return;
}

template <class Key>
bool ABE<Key>::insertar(const Key& k) {
	NodoAVL<Key>* nodo = reinterpret_cast<NodoAVL<Key>*>(this->raiz_);
	//std::cout << "Holaa \n\n" << *this << std::endl;
	return (insertar_recursivo(nodo, k));
}

template <class Key>
bool ABE<Key>::insertar_recursivo(NodoAVL<Key>*& nodo, const Key& k) {
	if (nodo == nullptr) {
		nodo = new NodoAVL<Key>(k);
		return true;
	} else {
		if (nodo->bal() == 0) {
			nodo->bal(-1);
			return insertar_recursivo(nodo->dcho(), k);
		} else
		if (nodo->bal() == -1) {
			nodo->bal(0);
			return insertar_recursivo(nodo->izdo(), k);
		}
	}
}

template <class Key>
bool ABE<Key>::buscar(const Key& k) const {
	return true;
}
#endif 