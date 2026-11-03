/*
* Universidad de La Laguna
* Escuela Superior de Ingenierí y Tecnología
* Grado en Ingenier´ıa Inform´atica
* Asignatura: Computabilidad y Algoritmia
* Curso: 2º
* Práctica 2: Cadenas y lenguajes
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 22/09/2024
* Archivo string.cc:
* Contiene la implementación de las funciones 
* de la clase string
* para definir el objeto cadena
* Referencias:
* Historial de Revisiones
*/

#include "string.h"
#include "language.h"

// Inicialización del método Lenght
// Retorna el tamaño de la cadena
int String::Lenght() const {
	if (string_ == "&") {
		return 0;
	}
	return string_.size();
}

// Inicialización del método reverse
// Retorna un String igual al invocante invertido
String String::Reverse() {
  std::string aux = get_string();
	std::string reverse_string = "";
  for (int i = aux.size() - 1; i >= 0; i--) {
    reverse_string += aux[i];
  }
	String result(reverse_string);
  return result;
}

// Inicialización del método Get_Prefixes
// Retorna un valor de tipo Language con todos los posibles prefijos
Language String::Get_Prefixes() {
	std::string aux = get_string();
	Language prefixes;
	prefixes.Insert("&");
	int j = 0;
	while (j < aux.size()) {
		std::string result = "";
		for(int i = 0; i <= j; i++) {
			result += aux[i];
		}
		prefixes.Insert(result);
		j++;
	}
	return prefixes;
}

// Inicialización del método Get_Suffixes
// Retorna un valor de tipo Language con todos los posibles sufijos
Language String::Get_Suffixes() {
	std::string aux = get_string();
	Language suffixes;
	suffixes.Insert("&");
	const int strsize = aux.size();
	int j = aux.size() - 1;
	while (j >= 0) {
		std::string result = "";
		for (int i = j; i < strsize; i++) {
			result += aux[i];
		}
		suffixes.Insert(result);
		j--;
	}
	return suffixes;
}

// Inicialización del operador de entrada
// Parámetros: is y instring de tipo istream y String respectivamente
std::istream& operator>>(std::istream& is, String& instring) {
	std::string aux;
	is >> aux;
	instring = String(aux);
	return is;
}

// Inicialización del operador de salida
// Parámetros: os y instring de tipo ostream y String respectivamente
std::ostream& operator<<(std::ostream& os, String& instring) {
	os << instring.get_string(); 
  return os;
}



// MODIFICACIÓN

String String::Pow(const int n) {
	const std::string first_string = string_;
	if (n == 0) {
		std::string empty_string = "&";
		String result(empty_string);
		return result;
	}
	if (first_string != "&") {
		for (int i = n; i > 1; i--) {
			string_ += first_string;
		}
		String result_string(string_);	
		return result_string;
	}
	return first_string;
}