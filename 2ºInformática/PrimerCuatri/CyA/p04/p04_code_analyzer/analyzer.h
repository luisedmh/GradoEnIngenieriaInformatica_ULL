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
* Archivo analyzer.h:
* Contiene la declaración de la calse Analyzer
* Referencias:
* Historial de Revisiones
*/

#ifndef ANALYZER
#define ANALYZER

#include <regex>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

#include "variable.h"
#include "loop.h"
#include "comment.h"

class Analyzer {
 public:
	Analyzer() = default;
	void AddVariable(const std::string& type, const std::string& line, int num_line);
	void AddLoop(const std::string& type, int num_line);
	void AddComment(const std::string& type, int top_line, int bottom_line, const std::string& content);
	void DetectMain() {has_Main_ = true;}
	void GenerateReport(std::ofstream& output_file, const std::string& file_name);
	void AnalyzeCode(std::istream& input_file);



	std::vector<Variable> get_variables() {return variables_;}
	std::vector<Loop> get_loops() {return loops_;}
	std::vector<Comment> get_comments() {return comments_;}
 private:
	std::string file_input_;
	std::string file_output_;
	std::vector<Variable> variables_;
  std::vector<Loop> loops_;
  std::vector<Comment> comments_;
  bool has_Main_;
};

#endif