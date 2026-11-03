/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Inteligencia Artificial
* Curso: 3º Práctica 01: Búsquedas no informadas
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 01/10/2025
* Archivo tools.h:                                                                                               
* Declaración de las funciones y structs de tools
* Referencias:
* Historial de Revisiones:
*/

#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// Struct para almacenar los resultados parciales e imprimirlos de manera más sencilla
struct Resultado {
	int iteracion;
	std::vector<int> generados;
	std::vector<int> inspeccionados;
};

// Struct para almacenar toda la entrada por terminal
struct Args {
	int estado_origen, estado_destino;
	std::string archivo_entrada, archivo_salida, modo_busqueda;
};

void MostrarAyuda();
Args ManejarArgumentos(int argc, char* argv[]);

#endif