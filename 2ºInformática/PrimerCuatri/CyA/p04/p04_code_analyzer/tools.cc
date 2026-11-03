/*
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Computabilidad y Algoritmia
* Curso: 2º
* Práctica 4: Expresiones regulares en C++
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 06/10/2024
* Archivo tools.cc:
* Contiene la implementación de las funcion usage
* Referencias:
* Historial de Revisiones
*/

#include "tools.h"

// Inicialización de la función Usage
// Parámetros: argc u argv de tipo int y puntero a char respectivamente
void Usage(int argc, char* argv[]) {
  if (argc != 3) {
    if (argc == 2) {
      std::string parameter = argv[1];
      if (parameter == "--help") {
        std::cout << "Modo de empleo: " << argv[0] << " filein.txt fileout.txt" << std::endl
                  << "El programa lee un archivo programado en C++ y devuelve en un fichero de salida donde se analiza dicho archivo" << std::endl;
        exit(0);
      }
		}
    std::cout << "Modo de empleo: " << argv[0] << " filein.txt fileout.txt" << std::endl
              << "Pruebe ’./p04_code_analyzer --help’ para más información." << std::endl;
    exit(0);
	}
}