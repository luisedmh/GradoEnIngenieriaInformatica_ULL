/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática* Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º
* Práctica 06: Implementación del TDA Árbol                                         
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 29/02/2025                                                                                                    
* Archivo main.cc:                                                                                                      
* Implementación de la función principal del programa                                                                         
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/  

#include "AVL.h"
#include "nif.h"
#include "tools.h"

int main(int argc, char* argv[]) {
  args options;
  std::vector<nif> nif_vector;
  try {
    options = parse_args(argc, argv);
    if (options.help) {
        help();
        return 0;
    }
    nif_vector = read_input(options.init, options.size, options.file);
  } catch (const std::exception& exception) {
    std::cerr << exception.what() << std::endl;
    return 1;
  }

  srand(time(0));

  AB<nif>* tree = nullptr;
  if (options.AVL) {
    tree = new AVL<nif>();
  } else {
    tree = new ABB<nif>();
  }
  make_tree(tree, nif_vector, options.trace, options.AVL);

  bool exit = false;
  while (!exit) {
    menu();
    short eleccion;
    std::cin >> eleccion;
    switch (eleccion) {
      case 0:
        exit = true;
        break;

      case 1: {
        std::cout << "¿Qué clave desea insertar? -> ";
        nif k;
        std::cin >> k;

        if (options.trace && options.AVL) {
          if (tree->buscar(k)) {
            std::cerr << "Esta clave ya ha sido insertada" << std::endl << std::endl;

          } else {
            std::cout << std::endl;
            std::cout << "Insertar: " << k << std::endl;
            tree->insertar_traza(k);
          }
      
        } else if (tree->insertar(k)) {
          std::cout << std::endl;
          std::cout << "Insertar: " << k << std::endl;
          std::cout << std::endl;
          std::cout << *tree << std::endl;
          std::cout << std::endl;

        } else {
          std::cerr << "Esta clave ya ha sido insertada" << std::endl << std::endl;
        }
        break;
      }
      case 2: {
        std::cout << "¿Qué clave desea buscar? ->";
        nif k;
        std::cin >> k;
        std::cout << std::endl;
        std::cout << (tree->buscar(k) ? "¡Clave encontrada!" : "¡Clave no encontrada!") << std::endl << std::endl;
        break;
      }
      case 3:{
        std::cout << std::endl;
        tree->inorden();
        std::cout << std::endl;
        break;
      }
      default: {
        std::cerr << "Opción incorrecta" << std::endl << std::endl;
        break;
      }
    }
  }
  return 0;
}
