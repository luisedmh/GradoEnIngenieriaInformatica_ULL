/*
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Computabilidad y Algoritmia
* Curso: 2º
* Práctica 4: Expresiones regulares en C++
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 08/10/2024
* Archivo analyze_class.h:
* Contiene la declaración de la calse AnalyzeClass
* Referencias:
* Historial de Revisiones
*/


#ifndef ANALYZECLASS
#define ANALYZECLASS

#include <string>

class AnalyzeClass {
 public:
	AnalyzeClass(const std::string& name_class, int line_class) : name_class_(name_class), line_class_(line_class) {}
	void AddUsed(const std::string& used, int line) {
		used_ = used;
		line_used_ = line;
		}
	std::string get_name() {return name_class_;}
	int get_line_class() {return line_class_;}
	int get_line_used() {return line_used_;}
	std::string get_used() {return used_;}
 private:
	std::string name_class_;
	int line_class_;
	std::string used_;
	int line_used_;
};

#endif