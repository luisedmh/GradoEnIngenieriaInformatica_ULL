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
* Archivo main.cc:
* Este código analiza un archivo de entrada en C++, identificando variables, 
* bucles, la función main, y comentarios (de una o varias líneas), almacenando 
* información relevante para cada elemento. Su objetivo es facilitar el análisis 
* estático del código fuente, como la detección de patrones o métricas.
* Referencias:
* Historial de Revisiones
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>   //for exit()
#include <string>
#include <vector>

#include "analyzer.h"
#include "variable.h"
#include "loop.h"
#include "comment.h"
#include "tools.h"

int main(int argc, char* argv[]) {
  Usage(argc, argv);

	std::string input_file = argv[1];
	std::string output_file = argv[2];

	std::ifstream input(input_file);
	if (!input.is_open()) {
			std::cout << "Error al abrir el fichero de entrada: " << input_file << std::endl;
			return 1;
	}

	std::ofstream output(output_file);
	if (!output.is_open()) {
			std::cout << "Error al abrir el fichero de entrada: " << output_file << std::endl;
			return 1;
	}

	Analyzer analyzer;
	analyzer.AnalyzeCode(input);
	analyzer.GenerateReport(output, input_file);

	input.close();
	output.close();
	
	return 0;
}