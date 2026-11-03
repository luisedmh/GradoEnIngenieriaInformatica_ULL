/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Inteligencia Artificial
* Curso: 3º Práctica 01: Búsquedas no informadas
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 01/10/2025
* Archivo grafo.cc:                                                                                               
* Implementación de la clase Grafo
* Referencias:
* Historial de Revisiones:
*/

#include "grafo.h"
#include <iomanip>
#include <stack>
#include <queue>

// Constructor
Grafo::Grafo(const std::string& nombre_archivo, const int origen, const int destino) {   
	estado_origen_ = origen;
	estado_destino_ = destino;
	num_aristas_ = 0;
	std::ifstream archivo(nombre_archivo);
	if (!archivo.is_open()) {
		throw std::runtime_error("No se pudo abrir el archivo: " + nombre_archivo);
	}

	archivo >> num_vertices_;

	grafo_.resize(num_vertices_);
	for (int i = 0; i < num_vertices_; i++) {
		grafo_[i].resize(num_vertices_, 0);
	}

	for (int i = 0; i < num_vertices_; i++) {
		grafo_[i][i] = 0;
	}

	for (int i = 0; i < num_vertices_ - 1; i++) {
		for (int j = i + 1; j < num_vertices_; j++) {
			float aux;
			archivo >> aux;
			if (aux != -1) {
				num_aristas_++;
			}
			grafo_[i][j] = aux;
			grafo_[j][i] = aux;
		}
	}
	archivo.close();
}


// Función extra para comprobar la entrada y ver el grafo
void Grafo::ImprimirGrafo(std::ostream& os) {
	for (int i = 0; i < num_vertices_; i++) {
		os << "[ ";
		for (int j = 0; j < num_vertices_; j++) {
			os << grafo_[i][j] << ", ";
		}
		os << " ]" << std::endl;
	}
}


// Método para comprobar estados repetidos en la misma rama
bool Grafo::EstadoRepetido(const std::vector<Nodo>& generados, Nodo* actual, int estado) {
	int i = actual->getIPadre();  // Usamos el índice del padre dentro del vector de generados en vez de un puntero (memoria dinámica)
	while (i != -1) {
		if (generados[i].getEstado() == estado) {
			return true;
		} else {
			i = generados[i].getIPadre();
		}
	}
	return false;
}


// Método para imprimir el resultado de cada iteración
void Grafo::ImprimirParcial(const Resultado& resultado, std::ostream& os) {
	os << "---------------------------------------------" << std::endl;
	os << "Iteración " << resultado.iteracion << std::endl;
	
	os << "Nodos generados: ";
	if (resultado.generados.empty()) {
		os << "-";
	} else {
		for (size_t i = 0; i < resultado.generados.size(); i++) {
			os << resultado.generados[i];
			if (i < resultado.generados.size() - 1) {
				os << ", ";
			}
		}
	}
	os << std::endl;
	
	os << "Nodos inspeccionados: ";
	if (resultado.inspeccionados.empty()) {
		os << "-";
	} else {
		for (size_t i = 0; i < resultado.inspeccionados.size(); i++) {
			os << resultado.inspeccionados[i];
			if (i < resultado.inspeccionados.size() - 1) {
				os << ", ";
			}
		}
	}
	os << std::endl;
}


// Método para imprimir el resultado final de la búsqueda
void Grafo::ImprimirResultado(const std::vector<Nodo>& generados, const Nodo* nodo_final, std::ostream& os) {
	std::stack<int> camino_resultado;
	Nodo nodo_hijo = *nodo_final;
	int estado_hijo = nodo_final->getEstado();
	camino_resultado.push(estado_hijo);

	int i = nodo_final->getIPadre();
	float coste = 0.0;

	while (i != -1) {
		int estado_padre = generados[i].getEstado();
		camino_resultado.push(estado_padre);

		if (((estado_padre - 1) >= 0) && ((estado_hijo - 1) >= 0)) {
			coste += grafo_[estado_padre - 1][estado_hijo - 1];
		}
		
		nodo_hijo = generados[i];
		estado_hijo = estado_padre;
		i = nodo_hijo.getIPadre();
	}
	os << "---------------------------------------------" << std::endl;
	os << "Camino: ";
	while (!camino_resultado.empty()) {
		os << camino_resultado.top();
		camino_resultado.pop();
		if (!camino_resultado.empty()) os << " -> ";
	}
	os << std::endl;
	os << "Costo total: " << coste << std::endl;
	os << "---------------------------------------------" << std::endl;
}


// Método para elegir que búsqueda hacer dependiendo de la entrada e imprimir los datos comunes del grafo
void Grafo::BNI(const std::string& modo_busqueda, std::ostream& os) {
	os << "---------------------------------------------" << std::endl;
	os << "Número de nodos del grafo: " << num_vertices_ << std::endl;
	os << "Número de aristas del grafo: " << num_aristas_ << std::endl;
	os << "Vértice origen: " << estado_origen_ << std::endl;
	os << "Vértice destino: " << estado_destino_ << std::endl;
	
	if (modo_busqueda == "DFS") {
		DFS(os);
	} else if (modo_busqueda == "BFS") {
		BFS(os);
	} else {
		throw std::runtime_error("Error: Tipo de búsqueda debe ser 'DFS' o 'BFS'");
	}
}


// Función que realiza la búsqueda en amplitud
void Grafo::BFS(std::ostream& os) {
	std::vector<Nodo> generados;	// Vector de nodos que han sido generados para conocer cual es el siguiente a inspeccionar
	int aux = 0; 	// Índice del siguiente a inspeccionar

	Resultado resultado;	// Struct complementario para guardar los resultados e imprimirlos facilmente
	resultado.iteracion = 1;
	resultado.generados.push_back(estado_origen_);
	
	generados.push_back(Nodo(estado_origen_, -1));	// Realizamos la primera iteración
	
	ImprimirParcial(resultado, os);

	bool destino_encontrado = false;

	Nodo* nodo_final = nullptr;

	while (!destino_encontrado && aux < generados.size()) {
		Nodo nodo_actual = generados[aux];		// nodo_actual es el nodo que estamos inspeccionando en esta iteración
		int estado_actual = nodo_actual.getEstado();
		
		if (estado_actual == estado_destino_) {	// Comprobamos si es el nodo destino una vez inspeccionado
			resultado.inspeccionados.push_back(estado_actual);
			resultado.iteracion++;
			ImprimirParcial(resultado, os);
			nodo_final = &generados[aux];
			destino_encontrado = true;
			break;
		}

		for (int i = 1; i <= num_vertices_; i++) {	// Generamos todos los hijos del nodo actual
			if (((i - 1) >= 0) && ((estado_actual - 1) >= 0)) {
				if ((grafo_[estado_actual - 1][i - 1] != -1) && (i != estado_actual) && !EstadoRepetido(generados, &nodo_actual, i)) {
					generados.push_back(Nodo(i, aux));
					// generados.push_back(Nodo(i, aux, nodo_actual.getCoste() + grafo_[estado_actual - 1][i - 1]));
					// std::cout << "Estado: " << generados[generados.size()-1].getEstado() << ", Coste acumulado: " << generados[generados.size()-1].getCoste() << std::endl;
					resultado.generados.push_back(i);
				}
			} else {
				throw std::out_of_range("Índice fuera de rango en BFS");
			}
		}

		resultado.inspeccionados.push_back(estado_actual);
		resultado.iteracion++;
		ImprimirParcial(resultado, os);

		aux++;	// Avanzamos el iterador de generados para inspeccionar el siguiente nodo, en BFS están ordenados directamente

	}

	if (destino_encontrado) {
		os << "---------------------------------------------" << std::endl;
		os << "Se ha encontrado el destino" << std::endl;
		ImprimirResultado(generados, nodo_final, os);
	} else {
		os << "---------------------------------------------" << std::endl;
		os << "No se encontró camino al destino" << std::endl;
	}
}


void Grafo::DFS(std::ostream& os) {
	std::vector<Nodo> generados;	// Vector de nodos que han sido generados para conocer cual es el siguiente a inspeccionar
	generados.push_back(Nodo(estado_origen_, -1));
	std::stack<int> pila;	// Como en DFS el orden de los nodos a inspeccionar no es el natural como en BFS usamos una pila equivalente a aux
	pila.push(0);

	Resultado resultado;	// Struct complementario para guardar los resultados e imprimirlos facilmente
	resultado.generados.push_back(estado_origen_);
	resultado.iteracion = 1;	// Realizamos la primera iteración antes del bucle
	ImprimirParcial(resultado, os);

	bool destino_encontrado = false;
	Nodo* nodo_final = nullptr;

	while (!destino_encontrado && !pila.empty()) {
		int indice_actual = pila.top();		// indice_actual es el equivalente a aux en BFS pero tenemos q sacarlo de la pila
		pila.pop();
		
		Nodo& nodo_actual = generados[indice_actual];		// nodo_actual es el nodo que vamos a inspeccionar en esta iteración
		int estado_actual = nodo_actual.getEstado();
		
		resultado.inspeccionados.push_back(estado_actual);
		
		if (estado_actual == estado_destino_) {		// Comprobamos si el estado que estamos inspeccionando es el esta destino
			nodo_final = &generados[indice_actual];
			destino_encontrado = true;
			break;
		}

		std::vector<int> hijos;		// Vector auxiliar necesario para darle la vuelta a los generados posteriormente
		for (int i = 1; i <= num_vertices_; i++) {		// Generamos los hijos de nodo_actual
			if (((i - 1) >= 0) && ((estado_actual - 1) >= 0)) {
				if ((grafo_[estado_actual - 1][i - 1] != -1) && (i != estado_actual) && !EstadoRepetido(generados, &nodo_actual, i)) {
					hijos.push_back(i);
					resultado.generados.push_back(i);	// resultado.generados y generados ya no contienen los estados en el mismo orden
				}
			} else {
				throw std::out_of_range("Índice fuera de rango en DFS");
			}
		}

		for (int i = hijos.size() - 1; i >= 0; i--) {
			int hijo = hijos[i];
			generados.push_back(Nodo(hijo, indice_actual));
			pila.push(static_cast<int>(generados.size() - 1));  // Guardamos el índice del nodo guardado en la pila, de esta manaera quedará en el top el siguiente nodo a inspeccionar
		}

		resultado.iteracion++;
		ImprimirParcial(resultado, os);
	}

	if (destino_encontrado) {
		resultado.iteracion++;
		ImprimirParcial(resultado, os);
		os << "---------------------------------------------" << std::endl;
		os << "Se ha encontrado el destino" << std::endl;
		ImprimirResultado(generados, nodo_final, os);
	} else {
		os << "---------------------------------------------" << std::endl;
		os << "No se encontró camino al destino" << std::endl;
	}
}


// int a = 10, b = 50;
// int num = a + (rand() % (b - a + 1)); 
// std::cout << "Número entre " << a << " y " << b << ": " << num << std::endl;

// si quieres enter 0 y 1:
// float num = (float)rand() / RAND_MAX;