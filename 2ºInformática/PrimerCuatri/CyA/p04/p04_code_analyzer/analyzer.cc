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
* Archivo analyzer.cc:
* Contiene la inicialización de la calse Analyzer y sus métodos
* Referencias:
* Historial de Revisiones
*/

#include "analyzer.h"


void Analyzer::AddVariable(const std::string& type, const std::string& line, int num_line) {
	Variable adding_variable(type, line, num_line);
	if (type == "INT") {
		adding_variable.AddInt();
	} else
	if (type == "DOUBLE") {
		adding_variable.AddDouble();
	}
	variables_.push_back(adding_variable);
}

void Analyzer::AddLoop(const std::string& type, int num_line) {
	Loop adding_loop(type, num_line);
	if (type == "while") {
		adding_loop.AddWhile();
	} else
	if (type == "for") {
		adding_loop.AddFor();
	}
	loops_.push_back(adding_loop);
}

void Analyzer::AddComment(const std::string& type, int top_line, int bottom_line, const std::string& content) {
	Comment adding_comment(type, top_line, bottom_line, content);
	comments_.push_back(adding_comment);
}

void Analyzer::AnalyzeCode(std::istream& input_file) {
	std::string line;
	int num_line = 0;

	std::regex regexInt("^\\s*(int) (.*);$");
	std::regex regexDouble("^\\s*(double) (.*);$");
	std::regex regexFor("^\\s*(for) ");
	std::regex regexWhile("^\\s*(while) ");
	std::regex regexMain("^\\s*int main\\s*\\(.*\\)");
	std::regex regexSimpleComment("^\\s*(//.*)$");
	std::regex regexComplexCommentBegin("^\\s*/\\*.*");
	std::regex regexComplexCommentEnd("\\*/\\s*$");

	std::smatch matches;

	while(getline(input_file, line)) {
		++num_line;
		if (regex_search(line, matches, regexInt)) {
			AddVariable("INT", matches[2], num_line);
		} else
		if (regex_search(line, matches, regexDouble)) {
			AddVariable("DOUBLE", matches[2], num_line);
		} else 
		if (regex_search(line, matches, regexFor)) {
			AddLoop("for", num_line);
		} else 
		if (regex_search(line, matches, regexWhile)) {
			AddLoop("while", num_line);
		} else
		if (regex_search(line, matches, regexSimpleComment)) {
			AddComment("single-line", num_line, num_line, matches[0]);
		} else 
		if (regex_search(line, matches, regexComplexCommentBegin)) {
			int top_line = num_line;
			std::string content = matches[0];
			content += '\n';
			while(getline(input_file, line)) {
				++num_line;
				content += (line + '\n');
				if(regex_search(line, matches, regexComplexCommentEnd)) {
					int bottom_line = num_line;
					if (top_line == 1) {
						AddComment("DESCRIPTION", top_line, bottom_line, content);
						break;
					} else {
						AddComment("multi-line", top_line, bottom_line, content);
						break;
					}
				}
			}
		} else
		if (regex_search(line, matches, regexMain)) {
			DetectMain();
		}
	}
}


void Analyzer::GenerateReport(std::ofstream& output_file, const std::string& file_name) {
	output_file << "PROGRAM: " << file_name << std::endl;

	bool has_description = false;
	if (comments_[0].get_type() == "DESCRIPTION") {
		has_description = true;
		output_file << "DESCRIPTION: " << std::endl;
		output_file << comments_[0].get_content() << std::endl;
	}
	output_file << "VARIABLES: " << std::endl;
	for (int i{0}; i < variables_.size(); i ++) {
		output_file << "[Line " << variables_[i].get_num_line() << "] " << variables_[i].get_type() << ": " << variables_[i].get_content() << std::endl;
	}
	output_file << std::endl;

	output_file << "STATEMENTS: " << std::endl;
	for (int i{0}; i < loops_.size(); i++) {
		output_file << "[Line " << loops_[i].get_num_line() << "] " << "LOOP: " << loops_[i].get_type() << std::endl;
	}
	output_file << std::endl;

	output_file << "MAIN: " << std::endl;
	if (has_Main_) {
		output_file << "True" << std::endl;
	} else {
		output_file << "False" << std::endl;
	}
	output_file << std::endl;

	output_file << "COMMENTS: " << std::endl;
	int j = 0;
	if (has_description) {
		output_file << "[Line " << comments_[0].get_top_line() << "-" << comments_[0].get_bottom_line() << "] " << comments_[0].get_type() << std::endl;
		j += 1;
	}
	for (int i = j; i < comments_.size(); i++) {
		if (comments_[i].get_type() == "single-line") {
			output_file << "[Line " << comments_[i].get_top_line() << "] " << comments_[i].get_content() << std::endl;
		} else 
		if (comments_[i].get_type() == "multi-line") {
			output_file << "[Line " << comments_[i].get_top_line() << "-" << comments_[i].get_bottom_line() << "] " << comments_[i].get_content() << std::endl; 
		}
	}
}