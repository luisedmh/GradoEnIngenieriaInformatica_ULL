#include <iostream>
#include <string>
#include "grafo.h"


int main(int argc, char* argv[]) {
	if (argc != 4) {
		std::cout << "Uso: " << argv[0] << " <archivo>" << std::endl;
		return 1;
	}

	std::string archivo = argv[1];
	int origen = std::stoi(argv[2]);
	int destino = std::stoi(argv[3]);
	
	// Crear grafo
	Grafo grafo(archivo, origen, destino);
	
	
	// Imprimir
	grafo.ImprimirGrafo();
	grafo.BFS();
	
	return 0;
}