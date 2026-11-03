#include <cstdlib>
#include <iostream>
#include <ctime>

#include "sequence.h"
#include "SortMethod.h"
#include "staticSequence.h"
#include "nif.h"
#include "insertion.h"
#include "shakeSort.h"
#include "tools.h"
#include "quickSort.h"
#include "heapSort.h"
#include "shellSort.h"

bool show_trace = false;

int main(int argc, char* argv[]) {
	SortMethod<nif>* sorter = nullptr;
	
	try {
		ProgramOptions opts = handle_arguments(argc, argv);
		
		if (opts.help_requested) {
			print_help();
			return 0;
		}
		
		staticSequence<nif> sequence(opts.sequence_size);
		initialize_sequence(sequence, opts.input_mode, opts.input_file);
		
		if (show_trace) {
			std::cout << "Iniciando traza de ejecución:\n";
		}
		
		switch (opts.sort_algorithm) {
			case INSERTION_SORT:
				sorter = new Insertion<nif>(sequence);
				break;
			case SHAKE_SORT:
				sorter = new ShakeSort<nif>(sequence);
				break;
			
			case QUICK_SORT:
				sorter = new QuickSort<nif>(sequence);
				break;
			case HEAP_SORT:
				sorter = new HeapSort<nif>(sequence);
				break;
			case SHELL_SORT:
				sorter = new ShellSort<nif>(sequence, opts.alpha);
				break;
		}
		
		sorter->Sort();
		
		std::cout << "Resultado de la ordenación:\n";
		std::cout << sorter->get_sequence() << "\n";
		
		delete sorter;
		return 0;
			
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << "\n";
		if (sorter != nullptr) {
			delete sorter;
		}
		return 1;
	}
}