/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática* Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º
* Práctica 06: Implementación del TDA Árbol                                         
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 29/02/2025                                                                                                    
* Archivo AVL.h:                                                                                                      
* Declaración e implementación de la clase AVL                                                                           
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/  

#ifndef AVL_H
#define AVL_H

#include "ABB.h"
#include "NodoAVL.h"

template <class Key>
class AVL : public ABB<Key> {
 public:
  AVL();
  bool insertar(const Key&) override;
  void insertar_traza(const Key&) override;
 private:
  void write_trace() const;
  void inserta_bal_trace(NodoAVL<Key>*&, NodoAVL<Key>*, bool&);
  void insert_re_balancea_izda_trace(NodoAVL<Key>*&, bool&);
  void insert_re_balancea_dcha_trace(NodoAVL<Key>*&, bool&);
};

template <class Key>
AVL<Key>::AVL() : ABB<Key>() {}

template <class Key>
void rotacion_II(NodoAVL<Key>*& nodo) {
  NodoAVL<Key>* nodo1 = nodo->izdo();
  nodo->izdo(nodo1->dcho());
  nodo1->dcho(nodo);
  if (nodo1->bal() == 1) {
     nodo->bal(0);
     nodo1->bal(0);
  } else {
    nodo->bal(1);
    nodo1->bal(-1);
  }
  nodo = nodo1;
}

template <class Key>
void rotacion_DD(NodoAVL<Key>*& nodo) {
  NodoAVL<Key>* nodo1 = nodo->dcho();
  nodo->dcho(nodo1->izdo());
  nodo1->izdo(nodo);
  if (nodo1->bal() == -1) {
    nodo->bal(0);
    nodo1->bal(0);
 	} else {
   	nodo->bal(-1);
   	nodo1->bal(1);
 	}
  nodo = nodo1;
}

template <class Key>
void rotacion_ID(NodoAVL<Key>*& nodo) {
  NodoAVL<Key>* nodo1 = nodo->izdo();
  NodoAVL<Key>* nodo2 = nodo1->dcho();
  nodo->izdo(nodo2->dcho());
  nodo2->dcho(nodo);
  nodo1->dcho(nodo2->izdo());
  nodo2->izdo(nodo1);
  if (nodo2->bal() == -1) {
		nodo1->bal(1);
	} else {
		nodo1->bal(0);
	}
  if (nodo2->bal() == 1) {
		nodo->bal(-1);
	} else {
		nodo->bal(0);
	}
  nodo2->bal(0);
  nodo = nodo2;
}

template <class Key>
void rotacion_DI(NodoAVL<Key>*& nodo) {
  NodoAVL<Key>* nodo1 = nodo->dcho();
  NodoAVL<Key>* nodo2 = nodo1->izdo();
  nodo->dcho(nodo2->izdo());
  nodo2->izdo(nodo);
  nodo1->izdo(nodo2->dcho());
  nodo2->dcho(nodo1);
  if (nodo2->bal() == 1) {
		nodo1->bal(-1);
	} else {
		nodo1->bal(0);
	}
  if (nodo2->bal() == -1) {
		nodo->bal(1);
	} else {
		nodo->bal(0);
	}
  nodo2->bal(0);
  nodo = nodo2;
}

template <class Key>
void insert_re_balancea_izda(NodoAVL<Key>*& nodo, bool& crece) {
  switch (nodo->bal()) {
    case -1:
      nodo->bal(0);
      crece = false;
      break;
    case 0:
      nodo->bal(1);
      break;
    case 1:
      NodoAVL<Key>* nodo1 = nodo->izdo();
      if (nodo1->bal() == 1) {
				rotacion_II(nodo);
			} else {
				rotacion_ID(nodo);
			}
      crece = false;
  }
}

template <class Key>
void insert_re_balancea_dcha(NodoAVL<Key>*& nodo, bool& crece) {
  switch (nodo->bal()) {
    case 1:
      nodo->bal(0);
      crece = false;
      break;
    case 0:
      nodo->bal(-1);
      break;
    case -1:
      NodoAVL<Key>* nodo1 = nodo->dcho();
      if (nodo1->bal() == -1) {
				rotacion_DD(nodo);
			} else {
				rotacion_DI(nodo);
			}
      crece = false;
  }
}

template <class Key>
void inserta_bal(NodoAVL<Key>*& nodo, NodoAVL<Key>* nuevo, bool& crece) {
  if (nodo == NULL) {
    nodo = nuevo;
    crece = true;
  } else 
	if (nuevo->dato() < nodo->dato()) {
    inserta_bal(nodo->izdo(), nuevo, crece);
    if (crece) {
			insert_re_balancea_izda(nodo, crece);
		}
  } else {
    inserta_bal(nodo->dcho(), nuevo, crece);
    if (crece) {
			insert_re_balancea_dcha(nodo, crece);
		}
  }
}

template <class Key>
void AVL<Key>::write_trace() const {
  std::queue<std::pair<NodoAVL<Key>*, int>> Q;
  NodoAVL<Key>* nodo = reinterpret_cast<NodoAVL<Key>*>(this->raiz_);
  int nivel, nivel_actual = 0;
  Q.push({nodo, 0});
  std::cout << "Nivel 0: ";
  while (!Q.empty()) {
    nodo = Q.front().first;
    nivel = Q.front().second;
    Q.pop();
    if (nivel > nivel_actual) {
      nivel_actual = nivel;
      std::cout << std::endl << "Nivel " << nivel << ": ";
    }
    if (nodo != nullptr) {
      std::cout << '[' << nodo->dato() << "(" << nodo->bal() << ")] ";
      Q.push({nodo->izdo(), nivel + 1});
      Q.push({nodo->dcho(), nivel + 1});
    } else {
      std::cout << "[·] ";
    }
  }
  std::cout << std::endl;
}


template <class Key>
bool AVL<Key>::insertar(const Key& k) {
  if (this->buscar(k)) {
		return false;
	}
  NodoAVL<Key>* nuevo = new NodoAVL<Key>(k);
  bool crece = false;
  inserta_bal(reinterpret_cast<NodoAVL<Key>*&>(this->raiz_), nuevo, crece);
  return true;
}

template <class Key>
void AVL<Key>::insert_re_balancea_izda_trace(NodoAVL<Key>*& nodo, bool& crece) {
  switch (nodo->bal()) {
    case -1:
      nodo->bal(0);
      crece = false;
      break;
    case 0:
      nodo->bal(1);
      break;
    case 1:
      nodo->bal(2);
      std::cout << "Desbalanceo:" << std::endl;
      write_trace();
      NodoAVL<Key>* nodo1 = nodo->izdo();
      std::cout << "Rotación " << (nodo1->bal() == 1 ? "II" : "ID") << " en [" << nodo->dato() << '(' << nodo->bal() << ")]:" << std::endl;
      if (nodo1->bal() == 1) {
				rotacion_II(nodo);
			} else {
				rotacion_ID(nodo);
			}
      crece = false;
  }
}

template <class Key>
void AVL<Key>::insert_re_balancea_dcha_trace(NodoAVL<Key>*& nodo, bool& crece) {
  switch (nodo->bal()) {
    case 1:
      nodo->bal(0);
      crece = false;
      break;
    case 0:
      nodo->bal(-1);
      break;
    case -1:
      nodo->bal(-2);
      std::cout << "Desbalanceo:" << std::endl;
      write_trace();
      NodoAVL<Key>* nodo1 = nodo->dcho();
      std::cout << "Rotación " << (nodo1->bal() == -1 ? "DD" : "DI") << " en [" << nodo->dato() << '(' << nodo->bal() << ")]:" << std::endl;
      if (nodo1->bal() == -1) {
				rotacion_DD(nodo);
			}
      else {
				rotacion_DI(nodo);
			}
      crece = false;
  }
}

template <class Key>
void AVL<Key>::inserta_bal_trace(NodoAVL<Key>*& nodo, NodoAVL<Key>* nuevo, bool& crece) {
  if (nodo == NULL) {
    nodo = nuevo;
    crece = true;
  } else if (nuevo->dato() < nodo->dato()) {
    inserta_bal_trace(nodo->izdo(), nuevo, crece);
    if (crece) {
			insert_re_balancea_izda_trace(nodo, crece);
		}
  } else {
    inserta_bal_trace(nodo->dcho(), nuevo, crece);
    if (crece) {
			insert_re_balancea_dcha_trace(nodo, crece);
		}
  }
}

template <class Key>
void AVL<Key>::insertar_traza(const Key& k) {
  NodoAVL<Key>* nuevo = new NodoAVL<Key>(k);
  bool crece = false;
  inserta_bal_trace(reinterpret_cast<NodoAVL<Key>*&>(this->raiz_), nuevo, crece);
  write_trace();
  std::cout << std::endl;
}


#endif