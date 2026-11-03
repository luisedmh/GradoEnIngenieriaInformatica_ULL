#include <iostream>

class Nodo {
 public:
	// Constructor
  Nodo(int estado, Nodo* padre = nullptr) : estado_(estado), nodo_padre_(padre) {}

	// Getters
	int getEstado() const { return estado_; }
	Nodo* getPadre() const { return nodo_padre_; }
	
 private:
	int estado_;
	Nodo* nodo_padre_;
};