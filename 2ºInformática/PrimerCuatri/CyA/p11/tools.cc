/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Computabilidad y Algoritmia
* Curso: 2º
* Práctica 11: Algoritmos Voraces (Greedy). Euclidean Minimum Spanning Tree
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 10/12/2024
* Archivo tools.cc:
* Implementación de la función Usage
* Referencias:
* Historial de Revisiones:
*/

#include "tools.h"

/**
 * @brief Función Usage para comprobar la entrada
 * @param argc Número de entradas por terminal
 * @param argv Entradas de terminal
 * @param d_option bool para saber si se ha añadido la ópcion d
 * @return bool que informa al main del estado de la entrada
 */
bool Usage(int argc, char* argv[], bool& d_option) {
	if (argc > 1) {
		if (std::string(argv[1]) == "-d") {
			d_option = true;
			if (argc == 3) {
				return true;
			} else {
				std::cerr << "No se incluyó el archivo de salida después de la opción -d" << std::endl;
			}
		} else 
		if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help") {
			std::cout << "Este programa calcula el Árbol Generador Mínimo Euclidiano (EMST) de un conjunto de puntos en el plano 2D utilizando el algoritmo de Kruskal." << std::endl;
			std::cout << "El árbol generado conecta todos los puntos con el menor costo total, basado en las distancias euclidianas entre ellos." << std::endl;
			std::cout << std::endl;
			std::cout << "Opciones disponibles:" << std::endl;
			std::cout << "  -d <nombre_archivo>  Generar un archivo DOT para la visualización del árbol en Graphviz." << std::endl;
			std::cout << "  -h | --help          Mostrar este mensaje de ayuda." << std::endl;
			std::cout << std::endl;
			std::cout << "Ejemplo de ejecución:" << std::endl;
			std::cout << "  ./EMST < puntos.txt  Ejecutar el programa con un conjunto de puntos desde la entrada estándar." << std::endl;
			std::cout << "  ./EMST -d salida.dot < puntos.txt  Generar el árbol en formato DOT y guardarlo en 'salida.dot'." << std::endl;
			exit(0);
		}
	} else 
	if (argc == 1) {
		return true;
	} 
	return true;
}