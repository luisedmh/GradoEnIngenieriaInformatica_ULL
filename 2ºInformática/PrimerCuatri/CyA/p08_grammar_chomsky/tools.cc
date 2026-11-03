/**
* Universidad de La Laguna
* Escuela Superior de Ingenierí y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Computabilidad y Algoritmia
* Curso: 2º
* Práctica 8: Gramáticas en Forma Normal de Chomsky
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 04/11/2024
* Archivo tools.cc:
* Implementación de la función Usage
* Referencias:
* Historial de Revisiones
*/

#include "tools.h"
/**
 * @brief Función que comprueba la correcta entrada del programa
 * @param argc int con la cantidad de parámetros de entrada
 * @param argv array de strings que contiene la entrada por línea de comandos
 * @return Ninguno
 */
void Usage(int argc, char* argv[]) {
  if (argc != 3) {
    if (argc == 2) {
      std::string parameter = argv[1];
      if (parameter == "--help") {
        std::cout << "1. Símbolos terminales (alfabeto): una línea que contiene N, el número de símbolos "
                 "en el alfabeto seguida de N líneas, cada una de las cuales contiene un símbolo del "
                 "alfabeto. Cada símbolo del alfabeto debe ser un único carácter imprimible.\n"
                 "2. Símbolos no terminales: una línea que contiene V, el número de símbolos no "
                 "terminales, seguida de V líneas, cada una de las cuales contiene una cadena alfanumérica "
                 "sin espacios. Se asumirá que el primero de los símbolos no terminales de esta lista será "
                 "el símbolo de arranque.\n"
                 "3. Producciones: una línea que contiene P, el número de producciones de la gramática, "
                 "seguida por P líneas cada una de las cuales contiene una producción en el formato:\n";
        exit(0);
      }
    }
    std::cout << "Modo de empleo: " << argv[0] << " input.gra output.gra" << std::endl
              << "Pruebe " << argv[0] << " --help para más información." << std::endl;
    exit(0);
  }
}