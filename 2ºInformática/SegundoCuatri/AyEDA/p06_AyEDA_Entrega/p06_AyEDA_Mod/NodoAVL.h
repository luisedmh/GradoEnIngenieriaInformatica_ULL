/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática* Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º
* Práctica 06: Implementación del TDA Árbol                                         
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 29/02/2025                                                                                                    
* Archivo NodoAVL.h:                                                                                                      
* Declaración e implementación de la clase NodoAVL                                                                           
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/  

#ifndef NODOAVL_H
#define NODOAVL_H

#include "NodoB.h"

template <class Key>
class NodoAVL : public NodoB<Key> {
 public:
  NodoAVL(const Key& dato = Key{}) : NodoB<Key>(dato), bal_(0) {
    this->izdo_ = nullptr;
    this->dcho_ = nullptr;
  }
  ~NodoAVL() { delete this->izdo_; delete this->dcho_; }

  short bal() const { return bal_; }
  void bal(const short bal) { bal_ = bal; }

  NodoAVL<Key>* izdo() const;
  NodoAVL<Key>*& izdo();
  void izdo(NodoAVL<Key>*);

  NodoAVL<Key>* dcho() const;
  NodoAVL<Key>*& dcho();
  void dcho(NodoAVL<Key>* dcho);

 private:
  short bal_;
};

template<class Key>
NodoAVL<Key>* NodoAVL<Key>::izdo() const { 
  return dynamic_cast<NodoAVL<Key>*>(this->izdo_); 
}

template<class Key>
NodoAVL<Key>*& NodoAVL<Key>::izdo() { 
	return reinterpret_cast<NodoAVL<Key>*&>(this->izdo_); 
}

template<class Key>
void NodoAVL<Key>::izdo(NodoAVL<Key>* izdo) {
	this->izdo_ = izdo;
}

template<class Key>
NodoAVL<Key>* NodoAVL<Key>::dcho() const {
	return dynamic_cast<NodoAVL<Key>*>(this->dcho_);
}

template<class Key>
NodoAVL<Key>*& NodoAVL<Key>::dcho() {
	return reinterpret_cast<NodoAVL<Key>*&>(this->dcho_);
}

template<class Key>
void NodoAVL<Key>::dcho(NodoAVL<Key>* dcho) {
	this->dcho_ = dcho;
}

#endif