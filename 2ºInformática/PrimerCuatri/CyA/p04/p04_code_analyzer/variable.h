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
* Archivo variable.h:
* Contiene la declaración de la calse Variable
* Referencias:
* Historial de Revisiones
*/


#ifndef VARIABLE
#define VARIABLE
  
#include <string>

class Variable {
 public:
 	Variable(std::string type, std::string line, int num_line) : type_(type), line_(line), num_line_(num_line), num_double_(0), num_int_(0) {}
	void AddInt() {num_int_ += 1;}
	void AddDouble() {num_double_ += 1;}

	std::string get_type() {return type_;}
	std::string get_content() {return line_;}
	int get_num_line() {return num_line_;}
 private:
 	std::string type_;
 	std::string line_;
 	int num_line_;
	int num_double_;
	int num_int_;
};

#endif