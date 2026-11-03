/**
* Universidad de La Laguna
* Escuela Superior de Ingenierí y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Computabilidad y Algoritmia
* Curso: 2º
* Práctica 6: Diseño y simulación de autómatas finitos
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 20/10/2024
* Archivo automaton.cc:
* Inicialización de los métodos de la clase Automaton que se encargará de generar
* un objeto con las funcionalidades de un autómata finito
* para definir el objeto cadena
* Referencias:
* Historial de Revisiones
*/

#include "automaton.h"
/**
 * @brief Constructor por defecto de la clase Automaton
 * @return Ninguno, crea un objeto
 */
Automaton::Automaton() : initial_state_(-1) {}

/**
 * @brief Método que carga la entrada del fichero .fa en un objeto de tipo Automaton
 * @param filename String con el nombre del fichero de entrada
 * @return Bool que devuelve true si fue posible cargar la información del fichero
 */
bool Automaton::LoadFromFile(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
			std::cerr << "Error al abrir el archivo: " << filename << std::endl;
			return false;
	}
	std::string line;
	// Símbolos del alfabeto separados por espacios
	std::getline(file, line);
	alphabet_ = Alphabet(line);
	for (const char check_char : alphabet_.get_alphabet()) {
		if (check_char == '&') {
			std::cerr << "El carácter & no puede formar parte de ningún alfabeto " << std::endl;
			return false;
		}
	}
	// Número total de estados del autómata.
	std::getline(file, line);
	int num_states_ = std::stoi(line);
	// Estado de arranque del autómata.
	std::getline(file, line);
	std::istringstream input_line(line);
	char input_char;
 	input_line >> input_char;
	char check_char;
	if (input_line >> check_char) {
		std::cerr << "Hay más de un estado de arranque" << std::endl;
		return false; 
	}	
	initial_state_ = input_char - '0';

	if (initial_state_ < 0 || initial_state_ >= num_states_) {
    std::cerr << "Problema con el estado de arranque" << std::endl;
    return false;
  }

	for (int i = 0; i < num_states_; ++i) {
		if (!std::getline(file, line)) {
			std::cerr << "No están declarados todos los estados" << std::endl;
			return false;
		}
		/*
		if (line.empty()) {
			std::cerr << "No están declarados todos los estados" << std::endl;
			return false;
		}
		*/
		std::istringstream input(line);
		int id, is_accept, num_transitions;
		input >> id >> is_accept >> num_transitions;
		State state(id, is_accept == 1);

		for (int j = 0; j < num_transitions; ++j) {
			char symbol;
			int dest;
			input >> symbol >> dest;
			if (!BelongsAlphabet(symbol)) {
				std::cerr << "El símbolo " << symbol << " no pertence al alfabeto." << std::endl;
				return false;
			}
			if (dest >= num_states_) {
				std::cerr << "Estado destino " << dest << " no perteneciente al autómata." << std::endl;
				return false;
			}
			if (dest < 0 || dest >= num_states_) {
        std::cerr << "El estado " << dest << " no existe." << std::endl;
        return false;
      }
			state.addTransition(symbol, dest);
		}

		states_.push_back(state);
	}

	file.close();
	return true;
}

/**
 * @brief Método que comprueba si un símbolo pertenece al alfabeto
 * @param symbol Char que representa el símbolo de entrada
 * @return Variable booleana que dice si pertenece o no dicho símbolo
 */
bool Automaton::BelongsAlphabet(const char symbol) const {
  std::set<char> alphabet = alphabet_.get_alphabet();
	if (symbol == '&') {
		return true;
	} else {
		for (char match_symbol : alphabet) {
			if (match_symbol == symbol) {
				return true;
			}
		}
		return false;
	}
}


/**
 * @brief Método que se encarga de leer cada cadena y comprobar si son pertenecientes al lenguaje representado por el autómata
 * @param input_string String con la cadena de entrada
 * @return Bool que devuelve si pertenece o no al lenguaje
 */
bool Automaton::Simulate(const std::string& input_string) {
	std::set<int> current_states;
	current_states.insert(initial_state_);
	current_states = EpsilonClosure(current_states);
	/*
	std::cout << "estados iniciales { ";
	for (auto astate : current_states) {
		std::cout << astate << ", ";
	}
	std::cout << "}" << std::endl;
	*/
	if (input_string == "&") {
		return IsFinal(current_states);
	}
	for (const char symbol : input_string) {
		if (!BelongsAlphabet(symbol)) {
			return false;
		}
		std::set<int> next_states;
		for (int state_id : current_states) {
			const State& state = states_[state_id];
			std::set<int> result = state.get_next_states(symbol);
			next_states.insert(result.begin(), result.end());
			/*
			std::cout << symbol << " -> {";
			for (auto astate : next_states) {
				std::cout << astate << ", ";
			}
			std::cout << " }" << std::endl;
			*/
		}
		current_states = next_states;
		current_states = EpsilonClosure(current_states);
		if (current_states.empty()) {
			return false;
		}
	}
	return IsFinal(current_states);
}

/**
 * @brief Método encargado de imprimir por pantalla si las cadenas del fichero de entrada 
 * dado pertencen al lenguaje representado por el autómata
 * @param input_filename String con el nombre del archivo de entrada
 * @return Ninguno, es un void
 */
void Automaton::FinalOutput(const std::string& input_filename) {
	std::ifstream file(input_filename);
	if (!file.is_open()) {
		std::cerr << "Error al abrir el archivo de entrada: " << input_filename << std::endl;
		return;
	}
	std::string line;
	int line_num = 1;
	while (std::getline(file, line)) {
		for (const char check : line) {
			if (!BelongsAlphabet(check)) {
				std::cerr << "El símbolo de la entrada de cadenas '" << check << "' no pertenece al alfabeto" << std::endl;
				std::cerr << "Error al cargar la entrada de cadenas a comprobar" << std::endl;
				exit(0);
			}
		}

		bool accepted = Simulate(line);
		std::cout << line_num << " " << line << " --- " 
							<< (accepted ? "Accepted" : "Rejected") << std::endl;
		line_num++;
	}

	file.close();
}

/**
 * @brief Método que comprueba si un estado es de aceptación
 * @param current_states Conjunto de los estados actuales
 * @return Bool que determina si es o no un estado de aceptación
 */
bool Automaton::IsFinal(const std::set<int>& current_states) {
	for (int id : current_states) {
		for (State state : states_) {
			if (state.get_id() == id && state.get_state_final()) {
				return true;
			}
		}
	}
	return false;
}

/**
 * @brief Métod que realiza la ε-clausura de un conjunto de estados
 * @param current_states Conjunto de estados actuales
 * @return Un nuevo conjunto de estado a partir de las ε-transiciones de los estados actuales
 */
std::set<int> Automaton::EpsilonClosure(const std::set<int>& current_states) const {
  std::set<int> closure = current_states;
  bool added = true;
  while (added) {
    added = false;
    for (const int id : closure) {
      auto range = states_[id].get_transitions().equal_range('&');
      for (auto it = range.first; it != range.second; ++it) {
        if (closure.insert(it->second).second) {
          added = true;
        }
      }
    }
  }
  return closure;
}
