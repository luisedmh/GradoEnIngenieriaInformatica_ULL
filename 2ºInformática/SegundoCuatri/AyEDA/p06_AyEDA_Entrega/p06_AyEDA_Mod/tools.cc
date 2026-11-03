/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática* Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º
* Práctica 06: Implementación del TDA Árbol                                         
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 29/02/2025                                                                                                    
* Archivo tools.cc:                                                                                                      
* Implementación de las funciones auxiliares para el programa principal                                                                      
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/  

#include "tools.h"

void menu() {
  std::cout << "[0] Salir" << std::endl;
  std::cout << "[1] Insertar clave" << std::endl;
  std::cout << "[2] Buscar clave" << std::endl;
  std::cout << "[3] Mostrar árbol inorden" << std::endl;
  std::cout << "Seleccione una opción: ";
}

void help() {
  std::cout << "Ejecución correcta del programa: " << std::endl;
  std::cout << "./tree -ab <abb|avl> -init <i> [s] [f] [-trace <y|n>]" << std::endl;
  std::cout << "-ab indica el tipo de árbol a usar" << std::endl;
  std::cout << "    abb -> árbol binario de búsqueda" << std::endl;
  std::cout << "    avl -> árbol binario de búsqueda balanceado" << std::endl;
  std::cout << "-init indica la forma de entrada del árbol." << std::endl;
  std::cout << "    manual." << std::endl;
  std::cout << "    random [s]" << std::endl;
  std::cout << "            s es el número de elementos a generar." << std::endl;
  std::cout << "    file [s] [f]" << std::endl;
  std::cout << "            s es el número de elementos a generar del fichero." << std::endl;
  std::cout << "            f es el nombre del fichero de entrada." << std::endl;
  std::cout << "-trace <y|n>" << std::endl;
  std::cout << "    y -> Muestra la traza de ejecución" << std::endl;
  std::cout << "    n -> no muestra la traza de ejecución" << std::endl;
}

args parse_args(int argc, char* argv[]) {
  args options;
  std::vector<std::string> args_list(argv, argv + argc);
  if (argc == 2 && args_list[1] == "--help") {
    options.help = true;
    return options;
  }
  if (argc < 5 || argc > 9) {
    throw std::invalid_argument("Parámetros incorrectos introduzca ./tree --help para más información");
  }
  for (int i = 1; i < argc; i++) {
    if (args_list[i] == "-ab") {
      if (args_list[++i] == "abb") {
        options.ABB = true;
      } else 
      if (args_list[i] == "avl") {
        options.AVL = true;
      } else 
      if (args_list[i] == "abe") {
        options.ABE = true;
      } else {
        throw std::invalid_argument("Opción no identificada de -ab");
      }
      //std::cerr << "ABB" << options.ABB << " AVL" << options.AVL << " ABE" << options.ABE << std::endl;
    } else 
    if (args_list[i] == "-init") {
      if (args_list[++i] == "manual") {
        options.init = 0;
      } else 
      if (args_list[i] == "random") {
        options.init = 0;
        try {
          options.size = std::stoul(args_list[++i]);
        } catch (...) {
          throw std::invalid_argument("Elija un número de elementos para -init random");
        }
      } else 
      if (args_list[i] == "file") {
        options.init = 1;
        try {
          options.size = std::stoul(args_list[++i]);
        } catch (...) {
          throw std::invalid_argument("Especifique la cantidad de elementos y el fichero de entrada para -init file");
        }
        options.file = args_list[++i];
      } else {
        throw std::invalid_argument("Opción no identificada de -init");
      }
    } else 
    if (args_list[i] == "-trace") {
      if (args_list[++i] == "y") {
        options.trace = true;
      } else 
      if (args_list[i] == "n") {
        options.trace = false;
      }
      else {
        throw std::invalid_argument("Opción no identificada de -trace");
      }
    } else {
      throw std::invalid_argument("Parámetro no conocido: " + args_list[i]);
    }
  }
  return options;
}

void make_tree(AB<nif>*& tree, std::vector<nif> nifs, bool trace, bool avl) {
  std::cout << "Árbol vacío" << std::endl;
  std::cout << "Nivel 0: [·]" << std::endl << std::endl;
  for (const nif n : nifs) {
    if (trace && avl) {
      if (tree->buscar(n)) {
        std::cerr << "La clave insertada ya se encuentra en el árbol" << std::endl << std::endl;
      } else {
        std::cout << std::endl;
        std::cout << "Insertar: " << n << std::endl;
        tree->insertar_traza(n);
      }
    } else if (tree->insertar(n)) {
      std::cout << std::endl;
      std::cout << "Insertar: " << n << std::endl;
      std::cout << *tree << std::endl;
    } else {
      std::cerr << "La clave insertada ya se encuentra en el árbol" << std::endl << std::endl;
    }
  }
}

std::vector<nif> read_input(bool init, const long size, const std::string& file) {
  std::vector<nif> nif_vector(size);
  if (init) {
    std::ifstream input_stream(file);
    if (!input_stream.is_open()) throw std::invalid_argument("Error al abrir el archivo " + file);
    for (int i = 0; i < size; i++) {
      nif tmp;
      if (input_stream >> tmp) nif_vector[i] = tmp;
      else nif_vector[i] = nif();
    }
  }
  return nif_vector;
}


