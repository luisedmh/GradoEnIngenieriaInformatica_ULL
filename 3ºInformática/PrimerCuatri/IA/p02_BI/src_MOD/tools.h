/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Inteligencia Artificial
* Curso: 3º Práctica 02: Búsquedas informadas
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 14/10/2025
* Archivo tools.h:                                                                                               
* Declaración de las funciones auxiliares
* Referencias:
* Historial de Revisiones:
*/

#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <vector>
#include <utility>
#include <cmath>

struct Args {
    std::string input_file;
    std::string output_file;
};

struct Datos {
    int iteracion;
    int reintentos;
    int coste;
    int coste_total = 0;
    int num_generados_iter;
    std::vector<std::pair<int, int>> generados;
    int num_inspeccionados_iter;
    std::vector<std::pair<int, int>> inspeccionados;
    int num_pasos;
    float proporcion_media;
    int num_generados_total = 0;;
    int num_inspeccionados_total = 0;
};

void MostrarAyuda(const std::string& program_name);
Args ObtenerArgs(int argc, char* argv[]);

#endif