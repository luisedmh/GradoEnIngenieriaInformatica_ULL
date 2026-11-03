/*
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Computabilidad y Algoritmia
* Curso: 2º
* Práctica 2: Cadenas y lenguajes
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 22/09/2024
* Archivo tools.cc:
* Contiene la implementación de las funcion usage
* Referencias:
* Historial de Revisiones
*/

#include "tools.h"

// Inicialización de la función Usage
// Parámetros: argc u argv de tipo int y puntero a char respectivamente
void Usage(int argc, char* argv[]) {
  if (argc != 4 && argc != 5) {
    if (argc == 2) {
      std::string parameter = argv[1];
      if (parameter == "--help") {
        std::cout << "Modo de empleo: " << argv[0] << " filein.txt fileout.txt opcode" << std::endl
                  << "Posibles opcodes: Alfabeto, Longitud, Inversa, Prefijos y Sufijos." << std::endl;
        exit(0);
      }
    } else
    if (argc == 5) {
      std::string parameter = argv[3];
      if (parameter != "Potencia") {
        std::cout << "Modo de empleo: " << argv[0] << " filein.txt fileout.txt opcode" << std::endl
                  << "Posibles opcodes: Alfabeto, Longitud, Inversa, Prefijos y Sufijos." << std::endl;
        exit(0);
      }
    }
    std::cout << "Modo de empleo: " << argv[0] << " filein.txt fileout.txt opcode" << std::endl
              << "Pruebe ’./p02_strings --help’ para más información." << std::endl;
    exit(0);
  }
}