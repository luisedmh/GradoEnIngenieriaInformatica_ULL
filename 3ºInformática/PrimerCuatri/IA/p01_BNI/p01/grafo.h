#include <iostream>
#include <vector>
#include <fstream>

#include "tools.h"
#include "nodo.h"

class Grafo {
 public:
	Grafo(const std::string& nombre_archivo, const int origen, const int destino);

	void ImprimirGrafo();

	Resultado BNI();

	void ImprimirParcial(const Resultado& resultado);
	void ImprimirResultado(const Nodo* nodo_final);
	
	bool EstadoRepetido(Nodo* actual, int estado);

	void DFS();
	void BFS();
	
 private:
	std::vector<std::vector<float>> grafo_;
	int num_vertices_;
	int num_aristas_;
	int estado_origen_;
	int estado_destino_;
};