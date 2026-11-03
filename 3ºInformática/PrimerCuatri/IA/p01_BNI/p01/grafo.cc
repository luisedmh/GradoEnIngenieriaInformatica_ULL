#include "grafo.h"
#include <iomanip>

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

void Grafo::ImprimirGrafo() {
	for (int i = 0; i < num_vertices_; i++) {
		std::cout << "[ ";
		for (int j = 0; j < num_vertices_; j++) {
			
			std::cout << grafo_[i][j] << ", ";
		}
		std::cout << " ]" << std::endl;
	}
}


void Grafo::ImprimirParcial(const Resultado& resultado) {
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << "Iteración " << resultado.iteracion << std::endl;
	
	// Nodos generados en esta iteración
	std::cout << "Nodos generados: ";
	if (resultado.estados_generados.empty()) {
		std::cout << "-";
	} else {
		for (size_t i = 0; i < resultado.estados_generados.size(); i++) {
			std::cout << resultado.estados_generados[i];
			if (i < resultado.estados_generados.size() - 1) {
				std::cout << ", ";
			}
		}
	}
	std::cout << std::endl;
	
	// Nodos inspeccionados en esta iteración  
	std::cout << "Nodos inspeccionados: ";
	if (resultado.estados_inspeccionados.empty()) {
		std::cout << "-";
	} else {
		for (size_t i = 0; i < resultado.estados_inspeccionados.size(); i++) {
			std::cout << resultado.estados_inspeccionados[i];
			if (i < resultado.estados_inspeccionados.size() - 1) {
				std::cout << ", ";
			}
		}
	}
	std::cout << std::endl << std::endl;
}

// void Grafo::ImprimirResultado(const Nodo* nodo_final) {
// 	float coste_total = 0;
// 	const Nodo* actual = nodo_final;
//   std::vector<int> camino;

// 	// Reconstruir camino y calcular coste en un solo recorrido
// 	while (actual != nullptr) {
// 		camino.push_back(actual->getEstado());
		
// 		// Calcular coste de esta arista (si hay padre)
// 		if (actual->getPadre() != nullptr) {
// 			int estado_padre = actual->getPadre()->getEstado();
// 			int estado_actual = actual->getEstado();
// 			coste_total += grafo_[estado_padre][estado_actual];
// 		}
		
// 		actual = actual->getPadre();
// 	}

// 	std::cout << "Camino: ";
// 	for (int i = static_cast<int>(camino.size()) - 1; i >= 0; i--) {
// 		if (i == 0) {
// 			std::cout << camino[i] << std::endl;
// 		} else {
// 			std::cout << camino[i] << " - ";
// 		}
// 	}
// 	std::cout << "Costo: " << coste_total << std::endl;
// }

void Grafo::ImprimirResultado(const Nodo* nodo_final) {
    float coste_total = 0;
    const Nodo* actual = nodo_final;
    std::vector<int> camino;

    // Reconstruir camino y calcular coste
    while (actual != nullptr) {
        camino.insert(camino.begin(), actual->getEstado());  // ✅ Insertar al principio
        
        if (actual->getPadre() != nullptr) {
            int estado_padre = actual->getPadre()->getEstado();
            int estado_actual = actual->getEstado();
            coste_total += grafo_[estado_padre - 1][estado_actual - 1];  // ✅ Ajustar índices
        }
        
        actual = actual->getPadre();
    }

    // ✅ CORREGIDO - Imprimir normalmente
    std::cout << "Camino: ";
    for (size_t i = 0; i < camino.size(); i++) {
        std::cout << camino[i];
        if (i < camino.size() - 1) {
            std::cout << " - ";
        }
    }
    std::cout << std::endl;
    std::cout << "Costo: " << std::fixed << std::setprecision(2) << coste_total << std::endl;
}


// float Grafo::CalcularCosteCamino(const Nodo* nodo_final) {
// 	float coste_total = 0.0f;
// 	const Nodo* actual = nodo_final;
	
// 	// Recorrer hacia atrás sumando costes de las aristas
// 	while (actual != nullptr && actual->getPadre() != nullptr) {
// 		int estado_padre = actual->getPadre()->getEstado();
// 		int estado_actual = actual->getEstado();
// 		coste_total += grafo_[estado_padre][estado_actual];
// 		actual = actual->getPadre();
// 	}
	
// 	return coste_total;
// }


bool Grafo::EstadoRepetido(Nodo* actual, int estado) {	
	
	// Recorrer la cadena de padres
	while (actual != nullptr) {
		if (actual->getEstado() == estado) {
			return true;  // Estado repetido en esta rama
		}
		actual = actual->getPadre();
	}
	return false;  // No repetido
}





void Grafo::DFS() {
	return;
}
// Resultado Grafo::BFS() {
// 	Resultado resultado;
	
// 	std::vector<Nodo> generados;
// 	std::vector<Nodo> inspeccionados;
// 	int aux_generados = 0;
// 	int aux_inspeccionar = 0;

// 	resultado.iteracion = 1;
// 	resultado.nodos_generados.push_back(nodo_origen_);

// 	generados.push_back(Nodo(nodo_origen_, nullptr));

// 	ImprimirParcial(reaultado);

// 	bool destino_encontrado = false;
// 	int estado_actual = nodo_origen_;
	
// 	Nodo nodo_actual = generados[aux_inspeccionar];
// 	aux_inspeccionar++;

// 	Nodo nodo_final;

// 	while(!destino_encontrado) {
// 		resultado.iteracion++;
// 		resultado.estados_inspeccionados.push_back(nodo_actual.getEstado());
// 		aux_inspeccionar++;
// 		inspeccionados.push_back(nodo_actual);
// 		for (int i = 0; i < num_vertices_; i++) {
// 			if ((grafo_[estado_actual][i] != -1) && !EstadoRepetido(generados[aux], estado_actual)) {
// 				generado.push_back(Nodo(i, *generados[aux_generados]));
// 				aux_generados++;
// 				resultado.estados_generados.push_back(i);
// 			}
// 		}

// 		ImprimirParcial(resultado);

// 		nodo_actual = generados[aux_inspeccionar];
		
// 		if (nodo_actual.getEstado() == nodo_destino_) {
// 			nodo_final = nodo_actual;
// 			destino_encontrado = true;
// 		}
// 	}

// 	void ImprimirCamino(nodo_final);

// }

void Grafo::BFS() {
	Resultado resultado;
	
	std::vector<Nodo> generados;
	std::vector<Nodo> inspeccionados;
	int aux_inspeccionar = 0;  // Índice del próximo nodo a expandir

	resultado.iteracion = 1;
	resultado.estados_generados.push_back(estado_origen_);

	// Nodo inicial (usando nullptr para el padre)
	generados.push_back(Nodo(estado_origen_, nullptr));

	ImprimirParcial(resultado);

	bool destino_encontrado = false;
	Nodo* nodo_final = nullptr;  // Usar puntero para el nodo final
	
	while(!destino_encontrado && aux_inspeccionar < generados.size()) {
		// Tomar el siguiente nodo a expandir
		Nodo& nodo_actual = generados[aux_inspeccionar];
		int estado_actual = nodo_actual.getEstado();
		
		resultado.iteracion++;
		resultado.estados_inspeccionados.push_back(estado_actual);
		inspeccionados.push_back(nodo_actual);
		
		// Verificar si es el destino ANTES de expandir
		if (estado_actual == estado_destino_) {
			nodo_final = &nodo_actual;
			destino_encontrado = true;
			break;  // Salir del bucle
		}
		
		// Expandir vecinos
		for (int i = 1; i <= num_vertices_; i++) {
			if ((grafo_[estado_actual - 1][i - 1] != -1) && !EstadoRepetido(&nodo_actual, i) && (estado_actual != i)) {
			// Crear nuevo nodo con puntero al padre actual
			generados.push_back(Nodo(i, &generados[aux_inspeccionar]));
			resultado.estados_generados.push_back(i);
			}
		}

		ImprimirParcial(resultado);
		aux_inspeccionar++;  // Pasar al siguiente nodo
	}

	if (nodo_final != nullptr) {
		ImprimirResultado(nodo_final);
	} else {
		std::cout << "No se encontró camino al destino" << std::endl;
	}
}