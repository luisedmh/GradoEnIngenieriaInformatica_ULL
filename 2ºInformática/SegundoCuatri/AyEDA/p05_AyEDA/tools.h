#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>

#include "sequence.h"
#include "SortMethod.h"
#include "staticSequence.h"
#include "nif.h"
#include "insertion.h"
#include "shakeSort.h"

extern bool show_trace;

enum SortAlgorithm {
	INSERTION_SORT = 1,
	SHAKE_SORT = 2,
	QUICK_SORT = 3,
	HEAP_SORT = 4,
	SHELL_SORT = 5
};

struct ProgramOptions {
	bool help_requested = false;
	unsigned sequence_size = 0;
	SortAlgorithm sort_algorithm = INSERTION_SORT;
	unsigned input_mode = 0; // 0=manual, 1=random, 2=file
	std::string input_file = "";
	double alpha = 0.0;
};

void print_help() {
	std::cout << "Uso del programa de ordenación:\n"
						<< "./sort -init <modo> [archivo] -size <tamaño> -ord <algoritmo> [alpha] [-trace <y|n>]\n\n"
						<< "Opciones:\n"
						<< "-init: Método de entrada de datos\n"
						<< "  manual   - Entrada manual\n"
						<< "  random   - Generación aleatoria\n"
						<< "  file <f> - Leer desde archivo\n\n"
						<< "-size: Tamaño de la secuencia\n\n"
						<< "-ord: Algoritmo de ordenación\n"
						<< "  1 - Inserción\n"
						<< "  2 - Sacudida\n"
						<< "  3 - QuickSort\n"
						<< "  4 - HeapSort\n"
						<< "  5 <α> - ShellSort (0 < α < 1)\n\n"
						<< "-trace: Mostrar traza (y/n)\n";
}

void initialize_sequence(staticSequence<nif>& seq, unsigned mode, const std::string& filename) {
	switch (mode) {
		case 0: // Manual
			std::cout << "Introduzca los " << seq.get_size() << " elementos:\n";
			std::cin >> seq;
			break;
		case 2: // Archivo
			std::ifstream file(filename);
			if (!file) {
				throw std::runtime_error("No se pudo abrir el archivo: " + filename);
			}
			file >> seq;
			break;
	}
}

ProgramOptions handle_arguments(int arg_count, char* arg_values[]) {
	ProgramOptions options;
	std::vector<std::string> args(arg_values, arg_values + arg_count);
	
	if (arg_count == 2 && args[1] == "--help") {
		options.help_requested = true;
		return options;
	}
	
	for (int i = 1; i < arg_count; ++i) {
		const std::string& arg = args[i];
		if (arg == "-init") {
			std::string mode = args[++i];
			if (mode == "manual") {
				options.input_mode = 0;
			} else
			if (mode == "random") {
				options.input_mode = 1;
			} else 
			if (mode == "file") {
				options.input_mode = 2;
				options.input_file = args[++i];
			} else {
				throw std::invalid_argument("Modo de inicialización no válido");
			}
		}
		else if (arg == "-size") {
			try {
				options.sequence_size = std::stoul(args[++i]);
			} catch (...) {
				throw std::invalid_argument("Tamaño de secuencia no válido");
			}
		}
		else if (arg == "-ord") {
			try {
				int alg = std::stoi(args[++i]);
				options.sort_algorithm = static_cast<SortAlgorithm>(alg);
				
				if (options.sort_algorithm == SHELL_SORT) {
					try {
						options.alpha = std::stod(args[++i]);
					} catch (...) {
						throw std::invalid_argument("Valor alpha no válido");
					}
				}
				
				if (alg < 1 || alg > 5) {
					throw std::invalid_argument("Algoritmo no reconocido");
				}
			} catch (...) {
				throw std::invalid_argument("Código de algoritmo no válido");
			}
		}
		else if (arg == "-trace") {
			std::string trace = args[++i];
			if (trace == "y") {
				show_trace = true;
			} else if (trace == "n") {
				show_trace = false;
			} else {
				throw std::invalid_argument("Valor de traza no válido (use y/n)");
			}
		}
		else {
			throw std::invalid_argument("Argumento desconocido: " + arg);
		}
	}
	
	return options;
}