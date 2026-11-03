/**
* Universidad de La Laguna
* Escuela Superior de Ingenierí y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Computabilidad y Algoritmia
* Curso: 2º
* Práctica 6: Diseño y simulación de autómatas finitos
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 20/10/2024
* Archivo tools.cc:
* Inicialización de la función Usage
* para definir el objeto cadena
* Referencias:
* Historial de Revisiones
*/

#include "tools.h"

/**
 * @brief Comprueba una entrada correcta desde lína de comandos
 * @param argc Cantidad de comandos de entrada por terminal
 * @param argv array de caracteres de dicha entrada
 * @return Ningnuno, es un void.
 */

void Usage(int argc, char* argv[]) {
  if (argc != 3) {
    if (argc == 2) {
      std::string parameter = argv[1];
      if (parameter == "--help") {
        std::cout << "Modo de empleo: " << argv[0] << " input.fa input.txt" << std::endl;
        std::cout << "El programa lee un archivo que contiene las especificaiones de un autómata finito" << std::endl;
        std::cout << "y comprueba si las cadenas dadas son pertenecientes al lenguaje representado por dicho autómata" << std::endl;
        exit(0);
      }
    }
    std::cout << "Modo de empleo: " << argv[0] << " input.fa input.txt" << std::endl;
    std::cout << "Pruebe ’p06_automata_simulator --help’ para más información." << std::endl;
    exit(0);
  }
}