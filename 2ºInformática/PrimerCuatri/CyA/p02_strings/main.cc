/*
* Universidad de La Laguna
* Escuela Superior de Ingenierí y Tecnología
* Grado en Ingenier´ıa Inform´atica
* Asignatura: Computabilidad y Algoritmia
* Curso: 2º
* Práctica 2: Cadenas y lenguajes
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 22/09/2024
* Archivo main.cc:
* Fichero main del programa para la ejecución del usuario
* para definir el objeto cadena
* Referencias:
* Historial de Revisiones
*/

#include <fstream>
#include <cstdlib> 		//exit
#include <iostream>
#include <string>
#include <set>
#include <sstream> 

#include "string.h"
#include "tools.h"
#include "alphabet.h"
#include "language.h"

typedef char Symbol;

int main(int argc, char* argv[]) {
// Llamada a la función Usage para comprobar la entrada
  Usage(argc, argv);
//Asignación de ficheros y Opcode
	std::string filein = argv[1], fileout = argv[2];
	std::string opcode = argv[3];
	int potencia;
	if (opcode == "Potencia") {
		potencia = atoi(argv[4]);
	}
	std::ifstream input_file(filein);
	std::ofstream output_file(fileout);
// Comprobación de ficheros
	if (!input_file.is_open() || !output_file.is_open()) {
    std::cout << "No se pudo abrir el archivo." << std::endl;
    return 1;
  }
	String instring;					// Declaración de la variable instring para la entrada
	Alphabet alphabet;				// Declaración de la variable alphabet para la entrada
	std::string line;
	// Bucle while que recibe la entrada línea a línea y realiza el opcode correspondiente
	while (std::getline(input_file, line)) {
		std::istringstream stream_line(line);
		std::string read_alphabet;
	  stream_line >> instring;
		bool appear_alphabet = false;			// variable para saber si se le asigna un alfabeto
	  if(stream_line >> read_alphabet) {
	   	alphabet = Alphabet(read_alphabet);
			appear_alphabet = true;
	  }
	// while (input_file >> instring >> alphabet) {
		if (opcode == "Alfabeto" && appear_alphabet) {
			output_file << alphabet << std::endl;
		} else
		if (opcode == "Longitud") {
			output_file << instring.Lenght() << std::endl;
		} else 
		if (opcode == "Inversa") {
			String result = instring.Reverse();
			output_file << result << std::endl;
		} else
		if (opcode == "Prefijos") {
			output_file << instring.Get_Prefixes() << std::endl;
		} else 
		if (opcode == "Sufijos") {
			output_file << instring.Get_Suffixes() << std::endl;
		} else 
		if (opcode == "Potencia") {
			String result = instring.Pow(potencia);
			output_file << result << std::endl;
		}
	}

	input_file.close();							// Cierra fichero de entrada
  output_file.close();						// Cierra fichero de salida
  return 0;												// Fin del main
}