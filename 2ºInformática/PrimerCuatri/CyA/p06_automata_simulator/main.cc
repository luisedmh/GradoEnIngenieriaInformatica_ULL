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
* Archivo main.cc:
* 
* para definir el objeto cadena
* Referencias:
* Historial de Revisiones
*/

#include "automaton.h"
#include "alphabet.h"
#include "state.h"
#include "tools.h"

#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>

int main(int argc, char* argv[]) {
	Usage(argc, argv);
	Automaton automaton;
	if (!automaton.LoadFromFile(argv[1])) {
		std::cerr << "Error al cargar el autómata." << std::endl;
		return 1;
	}
	automaton.FinalOutput(argv[2]);
	return 0;
}