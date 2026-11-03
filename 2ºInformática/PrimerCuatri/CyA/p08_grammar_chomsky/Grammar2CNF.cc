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
* Archivo Grammar2CNF.cc:
* Archivo que contiene el main que ejecutará un programa que recibe una gramática
* independiente del contexto y la devuelve en forma normal de Chomsky
* para definir el objeto cadena
* Referencias:
* Historial de Revisiones
*/

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <cstdlib>

#include "alphabet.h"
#include "not_terminal.h"
#include "grammar.h"
#include "tools.h"


/**
 * @brief Función main para el cliente, permite la ejecución del programa
 * @param argc Int que indica la cantidad de parametros de entrada por la línea de terminal
 * @param argv array de strings que contiene la entrada por línea de comandos
 * @return Int que sirve para indicar el funciomaniento del programa, correcto o no
 */
int main(int argc, char* argv[]) {
	Usage(argc, argv);
	std::string input_file_name = argv[1];
	std::ifstream input_file(input_file_name);
	std::string output_file_name = argv[2];
	std::ofstream output_file(output_file_name);
	if (!input_file.is_open()) {
    std::cerr << "No se pudo abrir el archivo de entrada" << std::endl;
    return 1;
  }
	if (!output_file.is_open()) {
    std::cerr << "No se pudo abrir el archivo de salida" << std::endl;
    return 1;
  }
	Grammar grammar(input_file);
	Grammar grammar_input;
	grammar_input = grammar;
	grammar.Transform_CNF();
	if (grammar.Check_Equal(grammar_input)) {
		std::cout << "La gramática ya está en forma normal de Chomsky" << std::endl;
		return 0;
	}
	grammar.Output_grammar(output_file);
	input_file.close();
	output_file.close();
	return 0;
}