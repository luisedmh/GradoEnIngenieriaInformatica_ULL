/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Inteligencia Artificial
* Curso: 3º Práctica 02: Búsquedas informadas
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 14/10/2025
* Archivo tools.cc:                                                                                               
* Implementación de las funciones auxiliares
* Referencias:
* Historial de Revisiones:
*/

#include "tools.h"
#include <iostream>
#include <stdexcept>

void MostrarAyuda(const std::string& program_name) {
    std::cout << "Uso: " << program_name << " <archivo_laberinto> [archivo_salida]" << std::endl;
    std::cout << "  archivo_laberinto: Archivo de texto con el laberinto" << std::endl;
    std::cout << "  archivo_salida:    Archivo donde guardar los resultados (opcional)" << std::endl;
}

Args ObtenerArgs(int argc, char* argv[]) {
    Args args;
    
    if (argc < 2) {
        MostrarAyuda(argv[0]);
        throw std::runtime_error("Número incorrecto de argumentos");
    }
    
    args.input_file = argv[1];
    
    // Si no se proporciona archivo de salida, usar uno por defecto
    if (argc == 3) {
        args.output_file = argv[2];
    } else {
        args.output_file = "ninguno";
    }
    
    return args;
}