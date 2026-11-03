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
* Archivo loop.h:
* Contiene la declaración de la calse Loop
* Referencias:
* Historial de Revisiones
*/


#ifndef LOOP
#define LOOP
#include <string>

class Loop {
 public:
	Loop(const std::string& type, int num_line) : type_(type), num_line_(num_line), num_for_(0), num_while_(0) {}
	void AddWhile() {num_while_ += 1;}
	void AddFor() {num_for_ += 1;}
	std::string get_type() {return type_;}
	int get_num_line() {return num_line_;}
 private:
	std::string type_;
	int num_line_;
	int num_for_;
	int num_while_;
};

#endif