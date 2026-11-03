/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Inteligencia Artificial
* Curso: 3º Práctica 01: Búsquedas no informadas
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 01/10/2025
* Archivo BNI.cc:                                                                                               
* Implementación de la función main
* Referencias:
* Historial de Revisiones:
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "grafo.h"
#include "tools.h"

int main(int argc, char* argv[]) {
	try {
		srand(time(0));
		Args args = ManejarArgumentos(argc, argv);  // Manejar los argumentos de entrada
		
		Grafo grafo(args.archivo_entrada, args.estado_origen, args.estado_destino); // Crear el grafo
		
		std::ofstream archivo_salida(args.archivo_salida);
		if (!archivo_salida.is_open()) {
			throw std::runtime_error("No se pudo abrir el archivo de salida: " + args.archivo_salida);
		}

		grafo.ImprimirGrafo();
		
		grafo.BNI(args.modo_busqueda, archivo_salida);  // Realizar la búsqueda correspondiente
		
		archivo_salida.close();
		std::cout << "Búsqueda completada. Resultados guardados en: " << args.archivo_salida << std::endl;
			
	} catch (const std::out_of_range& e) {
		std::cerr << "ERROR DE ÍNDICE FUERA DE RANGO: " << e.what() << std::endl;
		return 2;

	} catch (const std::runtime_error& e) {
		std::cerr << "ERROR DE EJECUCIÓN: " << e.what() << std::endl;
		std::cerr << "Use --help para ver la ayuda" << std::endl;
		return 1;

	} catch (const std::exception& e) {
		std::cerr << "ERROR DESCONOCIDO: " << e.what() << std::endl;
		return 3;
	}
	
	return 0;
}