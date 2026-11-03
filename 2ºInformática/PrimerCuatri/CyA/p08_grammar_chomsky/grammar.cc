/**
* Universidad de La Laguna
* Escuela Superior de Ingenierí y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Computabilidad y Algoritmia
* Curso: 2º
* Práctica 8: Gramáticas en Forma Normal de Chomsky
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 04/11/2024
* Archivo grammar.cc:
* Implementación de los métodos de la clase Grammar que se encargará de generar
* un objeto con las funcionalidades de una gramática
* para definir el objeto cadena
* Referencias:
* Historial de Revisiones
*/

#include "grammar.h"

#include "iostream"

/**
 * @brief Constructor a partir de una entrada de la clase Grammar
 * @param input_file stream de entrada
 * @return Ninguno, crea un objeto
 */

Grammar::Grammar(std::istream& input_file) {
	int amount_terminal, amount_not_terminals, amount_productions;
	input_file >> amount_terminal;
	for (int i = 0; i < amount_terminal; i++) {
		char terminal;
		input_file >> terminal;
		if (terminal < 'a' || terminal > 'z') {
			std::cerr << "El símbolo terminal " << terminal << " no cumple el convenio de notación" << std::endl;
			exit(1);
		}
		alphabet_.AddSymbol(terminal);
	}
	input_file >> amount_not_terminals;
	for (int i = 0; i < amount_not_terminals; i++) {
		char not_terminal;
		input_file >> not_terminal;
		if (not_terminal < 'A' || not_terminal > 'Z') {
			std::cerr << "El símbolo no terminal " << not_terminal << " no cumple el convenio de notación" << std::endl;
			exit(1);
		}
		not_terminal_.AddNotTerminal(not_terminal);
	}
	input_file >> amount_productions;
	std::string production;
	input_file >> start_not_terminal_ >> production;
	productions_.insert({start_not_terminal_, production});
	for (int i = 0; i < amount_productions - 1; i++) {
		char not_terminal;
		std::string production;
		input_file >> not_terminal >> production;
		if (production.size() <= 1 && production[0] == '&') {
			std::cerr << "La entrada de la producción " << not_terminal << " -> " << production << " no es válida ya que es una producción vacía" << std::endl;
			exit(1);
		} 
		if (production.size() <= 1 && (production[0] > 'A' && production[0] < 'Z')) {
			std::cerr << "La entrada de la producción " << not_terminal << " -> " << production << " no es válida ya que es una producción unitaria" << std::endl;
			exit(1);
		}
		
		productions_.insert({not_terminal, production});
	}
}

/**
 * @brief Método que se encarga de la salida de la clase Grammar
 * @param output_file stream de salida
 * @return Ninguno
 */
void Grammar::Output_grammar(std::ostream& output_file) {
	output_file << alphabet_.get_alphabet().size() << std::endl;
	for (const char terminal : alphabet_.get_alphabet()) {
		output_file << terminal << std::endl;
	}
	output_file << not_terminal_.get_not_terminal().size() << std::endl;
	for (const char not_terminal : not_terminal_.get_not_terminal()) {
    output_file << not_terminal << std::endl;
  }
	output_file << productions_.size() << std::endl;
	for (const auto& production : productions_) {
    if (production.first == start_not_terminal_) {
      output_file << production.first << " -> " << production.second << std::endl;
    }
	}
	for (const auto& production : productions_) {
    if (production.first != start_not_terminal_) {
      output_file << production.first << " -> " << production.second << std::endl;
    }
	}
}

/**
 * @brief Método que transforma en forma normal de Chomsky el objeto de tipo Grammar
 * @param void
 * @return Ninguno
 */
void Grammar::Transform_CNF() {
	std::map<char, char> new_productions;
	for (auto& production : productions_) {
		if (production.second.size() >= 2) {
			std::string result_second = "";
			for (char symbol : production.second) {
				if (alphabet_.get_alphabet().find(symbol) != alphabet_.get_alphabet().end()) {
					if (new_productions.find(symbol) == new_productions.end()) {
						char new_not_terminal;
						for (char i = 'A'; i <= 'Z'; i++) {
							if (not_terminal_.get_not_terminal().find(i) == not_terminal_.get_not_terminal().end()) {
								new_not_terminal = i;
								break;
							}
						}
						new_productions.insert({symbol, new_not_terminal});
						not_terminal_.AddNotTerminal(new_not_terminal);
						productions_.insert({new_not_terminal, std::string(1, symbol)});
						result_second += new_not_terminal;
					} else {
						result_second += new_productions.find(symbol)->second;
					}
				} else {
					result_second += symbol;
				}
			}
			production.second = result_second;
		}
	}
  bool changes = true;
  while (changes) {
    changes = false;
    for (auto& production : productions_) {
      if (production.second.length() >= 3) {
        changes = true;
        char new_not_terminal;
				for (char i = 'A'; i <= 'Z'; i++) {
				if (not_terminal_.get_not_terminal().find(i) == not_terminal_.get_not_terminal().end()) {
					new_not_terminal = i;
					break;
				}
				}
        not_terminal_.AddNotTerminal(new_not_terminal);
        productions_.insert({new_not_terminal, production.second.substr(1)});
        production.second = std::string(1, production.second[0]) + std::string(1, new_not_terminal);
      }
    }
  }
}

bool Grammar::Check_Equal(Grammar grammar_input) {
	if (alphabet_.get_alphabet() != grammar_input.get_first_alphabet().get_alphabet()) {
		return 0;
	}
	if (not_terminal_.get_not_terminal() != grammar_input.get_not_terminal().get_not_terminal()) {
		return 0;
	}
	if (productions_ != grammar_input.get_productions()) {
		return 0;
	}
	return 1;
}