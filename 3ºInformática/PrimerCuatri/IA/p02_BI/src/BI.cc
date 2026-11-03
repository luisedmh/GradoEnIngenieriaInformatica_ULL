/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Inteligencia Artificial
* Curso: 3º Práctica 02: Búsquedas informadas
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 14/10/2025
* Archivo BI.cc:                                                                                               
* Implementación de la función main del programa
* Referencias:
* Historial de Revisiones:
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

#include "tools.h"
#include "laberinto.h"
#include "nodo.h"

int main(int argc, char* argv[]) {
	srand(time(0));
	
	try {
		// Obtener argumentos usando tools
		Args args = ObtenerArgs(argc, argv);
		
		std::cout << "=== CARGANDO LABERINTO ===" << std::endl;
		std::cout << "Archivo de entrada: " << args.input_file << std::endl;
		std::cout << "Archivo de salida: " << args.output_file << std::endl;

		// Crear el laberinto
		Laberinto laberinto(args.input_file);
		// Salida dependiendo de si hay archivo de salida o no
		if (args.output_file == "ninguno") {
			std::cout << "\n=== LABERINTO ===" << std::endl;
			laberinto.ImprimirLaberinto();

			std::cout << "\n\n=== EJECUCIÓN DINÁMICA ===" << std::endl;
			laberinto.ResolverDinamico();
			
			std::cout << "\n=== EJECUCIÓN FINALIZADA ===" << std::endl;
		} else {
			std::ofstream salida(args.output_file);
			salida << "\n=== LABERINTO ===" << std::endl;
			laberinto.ImprimirLaberinto(salida);

			salida << "\n\n=== EJECUCIÓN DINÁMICA ===" << std::endl;
			laberinto.ResolverDinamico(salida);
			
			salida << "\n=== EJECUCIÓN FINALIZADA ===" << std::endl;
		}
		

	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}