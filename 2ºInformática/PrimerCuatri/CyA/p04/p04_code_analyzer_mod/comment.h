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
* Archivo comment.h:
* Contiene la declaración de la calse Comment
* Referencias:
* Historial de Revisiones
*/

#ifndef COMMENT
#define COMMENT

#include <string>

class Comment {
 public:
	Comment(const std::string& type, int top_line, int bottom_line, const std::string& content) 
				: type_(type), top_line_(top_line), bottom_line_(bottom_line), content_(content) {}

	std::string get_type() {return type_;}
	std::string get_content() {return content_;}
	int get_top_line() {return top_line_;}
	int get_bottom_line() {return bottom_line_;}
 private:
	std::string type_;
	int top_line_;
	int bottom_line_;
	std::string content_;
};

#endif