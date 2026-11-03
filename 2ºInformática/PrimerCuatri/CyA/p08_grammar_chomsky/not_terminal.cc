/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Computabilidad y Algoritmia
* Curso: 2º
* Práctica 8: Gramáticas en Forma Normal de Chomsky
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 04/11/2024
* Archivo not_terminal.cc:
* Implementación de las funciones de la clase
* NotTerminal que se encargará de generar
* un objeto con las funcionalidades de los símbolos no terminales
* para definir el objeto cadena
* Referencias:
* Historial de Revisiones
*/

#include "not_terminal.h"

/**
 * @brief Método que añade un símbolo a los no terminales
 * @param not_terminal Char del símbolo a añadir
 * @return Ninguno
 */
void NotTerminal::AddNotTerminal(const char not_terminal) {
	not_terminal_.insert(not_terminal);
}
