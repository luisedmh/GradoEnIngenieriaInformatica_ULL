/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática* Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º
* Práctica 06: Implementación del TDA Árbol                                         
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 29/02/2025                                                                                                    
* Archivo NodoB.h:                                                                                                      
* Declaración e implementación de la clase NodoB                                                                          
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/  

#ifndef NODOB_H
#define NODOB_H


template <class Key>
class NodoB {
public:
	NodoB(const Key& dato, NodoB<Key>* izdo = nullptr, NodoB<Key>* dcho = nullptr) 
			: dato_(dato), izdo_(izdo), dcho_(dcho) {}
	~NodoB() { delete izdo_; delete dcho_; }

	const Key& dato() const { return dato_; }

	NodoB<Key>* izdo() const { return izdo_; }
	NodoB<Key>*& izdo() { return izdo_; }

	NodoB<Key>* dcho() const { return dcho_; }
	NodoB<Key>*& dcho() { return dcho_; }

 protected:
	Key dato_;
	NodoB<Key>* izdo_;
	NodoB<Key>* dcho_;
};


#endif