
/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Inteligencia Artificial
* Curso: 3º Práctica 01: Búsquedas no informadas
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 01/10/2025
* Archivo tools.cc:                                                                                               
* Implementación de las funciones de tools
* Referencias:
* Historial de Revisiones:
*/

#include "tools.h"
#include <iostream>
#include <stdexcept>
#include <string>


// Función necesaria para el --help
void MostrarAyuda() {
	std::cout << "Uso: ./programa <ArchivoEntrada> <ArchivoSalida> <TipoBusqueda> <EstadoOrigen> <EstadoDestino>\n";
	std::cout << "Donde:\n";
	std::cout << "  ArchivoEntrada:  Ruta al archivo con la definición del grafo\n";
	std::cout << "  ArchivoSalida:   Ruta donde se guardarán los resultados\n";
	std::cout << "  TipoBusqueda:    DFS (Depth-First Search) o BFS (Breadth-First Search)\n";
	std::cout << "  EstadoOrigen:    Estado inicial (entero positivo)\n";
	std::cout << "  EstadoDestino:   Estado objetivo (entero positivo)\n\n";
	std::cout << "Ejemplo: ./programa grafo.txt resultado.txt DFS 1 15\n";
	std::cout << "         ./programa --help  Muestra esta ayuda\n";
}

// Función para obtener la entrada de terminal
Args ManejarArgumentos(int argc, char* argv[]) {
	Args args;
	
	if (argc == 2 && std::string(argv[1]) == "--help") {
		MostrarAyuda();
		exit(0);
	}
	
	if (argc != 6) {
		throw std::runtime_error("Error: Número incorrecto de argumentos. Use --help para ayuda.");
	}
	
	args.archivo_entrada = argv[1];
	args.archivo_salida = argv[2];
	args.modo_busqueda = argv[3];
	
	if (args.modo_busqueda != "DFS" && args.modo_busqueda != "BFS") {
		throw std::runtime_error("Error: Tipo de búsqueda debe ser 'DFS' o 'BFS'");
	}
	
	try {
		args.estado_origen = std::stoi(argv[4]);
		args.estado_destino = std::stoi(argv[5]);
	} catch (const std::exception& e) {
		throw std::runtime_error("Error: Estados origen y destino deben ser números enteros");
	}
	
	if (args.estado_origen <= 0 || args.estado_destino <= 0) {
		throw std::runtime_error("Error: Los estados deben ser números positivos");
	}
	
	return args;
}