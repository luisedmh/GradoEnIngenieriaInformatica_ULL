/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Inteligencia Artificial
* Curso: 3º Práctica 02: Búsquedas informadas
* Autor: Luis Eduardo Martín Hernández
* Correo: alu0101631134@ull.edu.es
* Fecha: 14/10/2025
* Archivo laberinto.cc:                                                                                               
* Implementación de la clase Laberinto
* Referencias:
* Historial de Revisiones:
*/

#include "laberinto.h"

#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"
#define CYAN    "\033[36m"

// Constructor del laberinto
Laberinto::Laberinto(const std::string& input_file) : filas_(0), columnas_(0), inicio_({-1, -1}), fin_({-1, -1}), num_paredes_(0) {
	
	std::ifstream archivo(input_file);
	if (!archivo.is_open()) {
		throw std::runtime_error("No se pudo abrir el archivo: " + input_file);
	}

	archivo >> filas_ >> columnas_;

	laberinto_.resize(filas_, std::vector<char>(columnas_));

	for (int i = 0; i < filas_; i++) {
		for (int j = 0; j < columnas_; j++) {
			char c;
			archivo >> c;
			if (c == '1') {
				num_paredes_++;
			}
			if (c == '3') {
				inicio_ = {i, j};
			} else
			if (c == '4') {
				fin_ = {i, j};
			}
			laberinto_[i][j] = c;
		}
	}

	std::cout << "Laberinto inicial cargado. ¿Desea cambiar el inicio y final?" << std::endl;
	std::string respuesta;
	std::cin >>	respuesta;
	if (respuesta == "sí" || respuesta == "Sí" || respuesta == "Si" || respuesta == "si" || respuesta == "Yes" || respuesta == "yes" || respuesta == "y" || respuesta == "Y" || respuesta == "S" || respuesta == "s") {
		std::cout << "Introduzca la nueva dirección de inicio del laberinto con el siguiente formato 'i j': ";
		int i;
		int j;
		std::cin >> i >> j;
		std::cout << std::endl;

		if ((i - 1) >= 0 && (j - 1) >= 0) {
			laberinto_[i - 1][j - 1] == '3';
			laberinto_[inicio_.first][inicio_.second] = '1';
			inicio_.first = i - 1;
			inicio_.second = j - 1;
		} else {
			laberinto_[i][j] == '3';
			laberinto_[inicio_.first][inicio_.second] = '1';
			inicio_.first = i;
			inicio_.second = j;
		}
		
		std::cout << "Introduzca la nueva dirección de fin del laberinto con el siguiente formato 'i j': ";
		std::cin >> i >> j;
		std::cout << std::endl;

		if ((i - 1) >= 0 && (j - 1) >= 0) {
			laberinto_[i - 1][j - 1] == '4';
			laberinto_[fin_.first][fin_.second] = '1';
			fin_.first = i - 1;
			fin_.second = j - 1;
		} else {
			laberinto_[i][j] == '4';
			laberinto_[fin_.first][fin_.second] = '1';
			fin_.first = i;
			fin_.second = j;
		}
	}
}

// Función que imprime el laberinto, usa colores si la salida es std::cout
void Laberinto::ImprimirLaberinto(std::ostream& os) {
	if (&os == &std::cout) {
		for (int i = 0; i < filas_; i++) {
			os << "|";
			for (int j = 0; j < columnas_; j++) {
				if (laberinto_[i][j] == '*') {
					os <<  RED << laberinto_[i][j] << RESET << "";
				} else
				if (laberinto_[i][j] == '3') {
					os << YELLOW << 'S' << RESET << "";
				} else 
				if (laberinto_[i][j] == '+') {
					os << GREEN << laberinto_[i][j] << RESET << "";
				} else 
				if (laberinto_[i][j] == '0') {
					os << " ";
				} else 
				if (laberinto_[i][j] == '1') {
					os << "█";
				} else 
				if (laberinto_[i][j] == '4') {
					os << CYAN << 'E' << RESET << "";
				} else {
					os << laberinto_[i][j] << " ";
				}
				
			}
			os << "|" << std::endl; 
		}
	} else {
		for (int i = 0; i < filas_; i++) {
			os << "|";
			for (int j = 0; j < columnas_; j++) {
				
				if (laberinto_[i][j] == '3') {
					os << 'S';
				} else 
				if (laberinto_[i][j] == '1') {
					os << "█";
				} else 
				if (laberinto_[i][j] == '4') {
					os << 'E';
				} else {
					os << laberinto_[i][j];
				}
				
			}
			os << "|" << std::endl; 
		}
	}
	
	
}

// Función que recoore los padres y regenera el camino
Nodo Laberinto::ImprimirCamino(const std::vector<Nodo>& inspeccionados, int aux, Datos& datos, std::ostream& os) {
    Laberinto laberinto_aux = *this;
    
    // Reconstruir camino
    std::vector<std::pair<int, int>> camino;
    int actual = aux;
	int i_hijo;
	int i_aux = aux;
	int i_aux2;
    
    while (actual != -1) {
        camino.insert(camino.begin(), inspeccionados[actual].getPos());  // Insertar al principio
        i_hijo = actual;
		actual = inspeccionados[actual].getIPadre();
    }

	while (i_aux != i_hijo) {
		i_aux2 = i_aux;
		i_aux = inspeccionados[i_aux].getIPadre();
	}
    
	datos.num_pasos = camino.size() - 1;
    for (size_t i = 1; i < camino.size(); i++) {
        laberinto_aux.laberinto_[camino[i].first][camino[i].second] = '*';
    }
    
	 // Mostrar información completa del camino
    os << "\n=== INFORMACIÓN DEL CAMINO ENCONTRADO ===" << std::endl;
    os << "Iteración: " << datos.iteracion << std::endl;
    os << "Reintentos: " << datos.reintentos << std::endl;
    os << "Coste del camino: " << datos.coste << std::endl;
    os << "Nodos generados en esta iteración: " << datos.num_generados_iter << std::endl;
    os << "Nodos inspeccionados en esta iteración: " << datos.num_inspeccionados_iter << std::endl;
    os << "Número de pasos del camino: " << datos.num_pasos << std::endl;
    os << "Proporción media de paredes: " << datos.proporcion_media << std::endl;
    
    // Mostrar nodos generados
    os << "\nNodos generados (" << datos.generados.size() << "): ";
    for (size_t i = 0; i < datos.generados.size(); i++) {
        os << "(" << datos.generados[i].first << "," << datos.generados[i].second << ")";
        if (i < datos.generados.size() - 1) os << ", ";
    }
    os << std::endl;
    
    // Mostrar nodos inspeccionados
    os << "Nodos inspeccionados (" << datos.inspeccionados.size() << "): ";
    for (size_t i = 0; i < datos.inspeccionados.size(); i++) {
        os << "(" << datos.inspeccionados[i].first << "," << datos.inspeccionados[i].second << ")";
        if (i < datos.inspeccionados.size() - 1) os << ", ";
    }
    os << std::endl;

    laberinto_aux.ImprimirLaberinto(os);	
	os << "Camino encontrado: ";
    for (size_t i = 0; i < camino.size(); i++) {
        os << "(" << camino[i].first << "," << camino[i].second << ")";
        if (i < camino.size() - 1) os << " -> ";
    }
    os << std::endl;
    
    // Devolver el primer movimiento (camino[1])
    if (camino.size() > 1) {
		Nodo nodo_aux(camino[1].first, camino[1].second);
		if (i_aux2 < inspeccionados.size()) {
			//std::cout << inspeccionados[i_nieto].getCosteAcumulado() << std::endl;
			nodo_aux.setCosteAcumulado(inspeccionados[i_aux2].getCosteAcumulado());
		}
		
        return nodo_aux;
    } else {
		Nodo nodo_aux (camino[0].first, camino[0].second);
		if (i_hijo < inspeccionados.size()) {
			nodo_aux.setCosteAcumulado(inspeccionados[i_aux2].getCosteAcumulado());
		}
        return nodo_aux;
    }
}

// Método específico para imprimir el camino final del dinámico
void Laberinto::ImprimirCaminoFinal(const std::vector<Nodo>& inspeccionados, int aux, Datos& datos, std::ostream& os) {
    Laberinto laberinto_aux = *this;
    
    // Reconstruir camino
    std::vector<std::pair<int, int>> camino;
    int actual = aux;
    
    while (actual != -1) {
        camino.insert(camino.begin(), inspeccionados[actual].getPos());  // Insertar al principio
        actual = inspeccionados[actual].getIPadre();
    }
    
	datos.num_pasos = camino.size() - 1;
    for (size_t i = 1; i < camino.size(); i++) {
        laberinto_aux.laberinto_[camino[i].first][camino[i].second] = '*';
    }
    
	// Mostrar solo la información requerida por la tabla
    os << "\n=== RESUMEN FINAL DEL CAMINO ===" << std::endl;
    os << "Laberinto: " << filas_ << "x" << columnas_ << std::endl;
    os << "Número de filas: " << filas_ << std::endl;
    os << "Número de columnas: " << columnas_ << std::endl;
    os << "Inicio (S): (" << camino[0].first << ", " << camino[0].second << ")" << std::endl;
    os << "Fin (E): (" << camino.back().first << ", " << camino.back().second << ")" << std::endl;
    
    // Mostrar camino compacto
    os << "Camino: ";
    for (size_t i = 0; i < camino.size(); i++) {
        os << "(" << camino[i].first << "," << camino[i].second << ")";
        if (i < camino.size() - 1) os << " -> ";
    }
    os << std::endl;
    
    os << "Coste: " << datos.coste_total << std::endl;
    os << "Número de nodos generados: " << datos.num_generados_total << std::endl;
    os << "Número de nodos inspeccionados: " << datos.num_inspeccionados_total << std::endl;
    
    os << "\nRepresentación visual final:" << std::endl;
    laberinto_aux.ImprimirLaberinto(os);
    os << "==============================\n" << std::endl;
}

// Heurística de Manhattan
int Laberinto::CalcularCosteEstimado(const Nodo& nodo) {
	const int W = 3;
	int coste_estimado = ((std::abs(fin_.first - nodo.getPos().first) + std::abs(fin_.second - nodo.getPos().second)) * W) + nodo.getCosteAcumulado();
	return coste_estimado;
}

// Heurística Euclidiana
int Laberinto::CalcularCosteEstimadoEuclidiano(const Nodo& nodo) {
    const int W = 3;
    int dx = fin_.first - nodo.getPos().first;
    int dy = fin_.second - nodo.getPos().second;
    int distancia_euclidiana = static_cast<int>(std::sqrt(dx*dx + dy*dy) * W);
    int coste_estimado = distancia_euclidiana + nodo.getCosteAcumulado();
    return coste_estimado;
}

// Función q realiza la búsqueda A* de cada iteración
Nodo Laberinto::ResolverEstatico(Datos& datos, std::ostream& os) {
	std::vector<Nodo> inspeccionados;
	int aux = 0;	// Iterador del vector de inspeccionados
	
	std::vector<Nodo> frontera;

	Nodo nodo_inicial(inicio_.first, inicio_.second, -1, 0);
	int estimado_nodo_inicial = CalcularCosteEstimado(nodo_inicial);
	// int estimado_nodo_inicial = CalcularCosteEstimadoEuclidiano(nodo_inicial);
	nodo_inicial.setCosteEstimado(estimado_nodo_inicial);
	
	inspeccionados.push_back(nodo_inicial);		// El nodo inicial va a ser el primero en inspeccionarse
	
	const std::vector<std::pair<int, int>> Direcciones = {
		{-1, 0},	// Arriba
		{1, 0},		// Abajo  
		{0, -1},	// Izquierda
		{0, 1},		// Derecha
		{-1, -1},	// Diagonal superior izquierda
		{-1, 1},	// Diagonal superior derecha
		{1, -1},	// Diagonal inferior izquierda
		{1, 1}		// Diagonal inferior derecha
	};
	const std::vector<int> Costes = {5, 5, 5, 5, 7, 7, 7, 7};

	bool final_encontrado = false;

	datos.num_inspeccionados_iter = 0;
	datos.num_generados_iter = 0;

	while (aux < inspeccionados.size() && !final_encontrado) {
		Nodo actual = inspeccionados[aux];
		datos.inspeccionados.push_back(actual.getPos());
		datos.num_inspeccionados_iter++;
		
		if (actual.getPos().first == fin_.first && actual.getPos().second == fin_.second) {
			final_encontrado = true;
			datos.coste = actual.getCosteAcumulado();
			Nodo nodo_siguiente = ImprimirCamino(inspeccionados, aux, datos, os);
			datos.coste_total += nodo_siguiente.getCosteAcumulado();
			//std::cout << nodo_siguiente.getCosteAcumulado() << std::endl;
			//std::cout << datos.coste_total << std::endl;
			return nodo_siguiente;
			break;
		}

		// Generar los nodos vecinos
		for (int i = 0; i < Direcciones.size(); i++) {
			int nueva_fila = actual.getPos().first + Direcciones[i].first;
			int nueva_columna = actual.getPos().second + Direcciones[i].second;
			// Verificar límites del laberinto
			if (nueva_fila >= 0 && nueva_fila < filas_ && nueva_columna >= 0 && nueva_columna < columnas_) {
				if (laberinto_[nueva_fila][nueva_columna] != '1') {
					
					int coste_acumulado = actual.getCosteAcumulado() + Costes[i];
					Nodo vecino(nueva_fila, nueva_columna, aux, coste_acumulado);
					int coste_estimado = CalcularCosteEstimado(vecino);
					// int coste_estimado = CalcularCosteEstimadoEuclidiano(vecino);
					vecino.setCosteEstimado(coste_estimado);
					
					// VERIFICAR SI DEBEMOS AÑADIR EL VECINO A FRONTERA
					bool en_inspeccionados = false;
					bool en_frontera = false;
					int indice_en_frontera = -1;
					
					// Comprobar si está en inspeccionados
					for (const auto& nodo : inspeccionados) {
						if (nodo.getPos() == vecino.getPos()) {
							en_inspeccionados = true;
							break;
						}
					}
					if (!en_inspeccionados) {
						// Comprobar si está en frontera y obtener su índice
						for (int j = 0; j < frontera.size(); j++) {
							if (frontera[j].getPos() == vecino.getPos()) {
								en_frontera = true;
								indice_en_frontera = j;
								break;
							}
						}
						
						// Lógica de añadido según las reglas
						if (!en_frontera) {
							// No está ni en inspeccionados ni en frontera -> Añadir a frontera
							frontera.push_back(vecino);
							datos.generados.push_back(vecino.getPos());
							datos.num_generados_iter++;
						}
						else if (en_frontera) {
							// Está en frontera -> Comparar costes y actualizar si es mejor
							if (vecino.getCosteEstimado() < frontera[indice_en_frontera].getCosteEstimado()) {
								frontera[indice_en_frontera] = vecino;  // Reemplazar con mejor camino
							}
						}
					}
				}
			}

		}
		// Seleccionar el mejor nodo de la frontera para la siguiente iteración
			if (!frontera.empty()) {
				int mejor_indice = 0;
				for (int i = 1; i < frontera.size(); i++) {
						if (frontera[i].getCosteEstimado() < frontera[mejor_indice].getCosteEstimado()) {
								mejor_indice = i;
						}
				}
				inspeccionados.push_back(frontera[mejor_indice]);
				frontera.erase(frontera.begin() + mejor_indice);
			}
			aux++;
	}
	if (!final_encontrado) {
		os << "No se ha encontrado un final" << std::endl;
		throw std::runtime_error("No se encontró camino al final");
	}

	
	Nodo nodo;
	return (nodo);
}

// Método para el comportamiento dinámico del labernto
void Laberinto::MezclarLaberinto() {
	const float P_in = 0.5;
	const float P_out = 0.5;
	const float Porcentaje_max = 0.35; // Intentamos q esté alrededor del 25% por eso puse de maximo 35
	
	int size = filas_ * columnas_;
	int num_paredes_max = static_cast<int>(size * Porcentaje_max);

	for (int i = 0; i < filas_; i++) {
		float porcentaje_actual = static_cast<float>(num_paredes_) / size;
    	float dinamicP_in = P_in * (1.0f - (porcentaje_actual / Porcentaje_max)); // Vamos adaptando la posibilidad de crear paredes nuevas a la cantidad 
		for (int j = 0; j < columnas_; j++) {
			float num = (float)rand() / RAND_MAX;
			if (laberinto_[i][j] == '1' && num <= P_out) {
				laberinto_[i][j] = '0';
				num_paredes_--;
			} else
			if (laberinto_[i][j] == '0' && num <= dinamicP_in) {
				laberinto_[i][j] = '1';
				num_paredes_++;
			}
		}
	}
	bool exceso_paredes = num_paredes_max <= num_paredes_ ? true : false;
	if (exceso_paredes) {
		MezclarLaberinto(); // Recursividad por si nos pasamos del 35%
	}
}

// Método q resuelve el laberinto dinámico
void Laberinto::ResolverDinamico(std::ostream& os) {
	std::vector<Nodo> camino; 	// Vector auxiliar q servirá para guardar los nodos del camino con sus iteradores en este vector
	int aux = 0;
	
	Datos datos;

	int size = filas_ * columnas_;

	const int Num_iter_max = 5;  // Máximo de reintentos sin éxito en un laberinto
	// La primera iteración es la del nodo inicial
	
	int i = 0;
	Nodo nodo_inicial(inicio_.first, inicio_.second, -1, 0);
	int estimado_nodo_inicial = CalcularCosteEstimado(nodo_inicial);
	// int estimado_nodo_inicial = CalcularCosteEstimadoEuclidiano(nodo_inicial);
	nodo_inicial.setCosteEstimado(estimado_nodo_inicial);
	camino.push_back(nodo_inicial);
	
	
	datos.iteracion = 0;
	datos.num_generados_iter = 1;
	datos.num_inspeccionados_iter = 0;
	datos.num_generados_total = 1;
	datos.generados.push_back(inicio_);
	datos.proporcion_media = static_cast<float>(num_paredes_) / size;
	datos.reintentos = i;
	datos.num_pasos = 0;
	// ImprimirParcial(datos);

	bool final_encontrado = false;
	
	while(!final_encontrado && i < Num_iter_max) {
		try {
			datos.iteracion++;
			datos.proporcion_media = static_cast<float>(num_paredes_) / size;

			datos.num_generados_iter = 0;
            datos.num_inspeccionados_iter = 0;
            datos.generados.clear();
            datos.inspeccionados.clear();
			
			Nodo nodo_actual = ResolverEstatico(datos, os);	// Resolver estático nos devuelve el nodo siguiente al inicial una vez resuelto el laberinto
			
			datos.num_generados_total += datos.num_generados_iter;
            datos.num_inspeccionados_total += datos.num_inspeccionados_iter;
			
			nodo_actual.setIPadre(aux);	// El padre de ese nood inicial era el que estamos inspeccionando
			
			if (nodo_actual.getPos().first == fin_.first && nodo_actual.getPos().second == fin_.second) {
				final_encontrado = true;
				os << "===============================================" << std::endl;
				os << "Camino dinámico encontrado" << std::endl;
				camino.push_back(nodo_actual);
				aux++;
				ImprimirCaminoFinal(camino, aux, datos, os);
				return;
			}
			camino.push_back(nodo_actual);
			aux++;
			laberinto_[nodo_actual.getPos().first][nodo_actual.getPos().second] = '+';
			setInicio(nodo_actual.getPos().first, nodo_actual.getPos().second);	// Cambiamos el laberinto avanzando el nodo incial
			MezclarLaberinto();
			i = 0;	// Reiniciamos los reintentos a 0
		} catch (const std::runtime_error& e) {
			i++;			
			if (i < Num_iter_max) {
				os << "Reorganizando laberinto..." << std::endl;
				MezclarLaberinto();
			} else {
				os << "Destino inalcanzable después de " << Num_iter_max << " reintentos" << std::endl;
				return;
			}
		}	
	}
}


// Generar números aleatorios
// int a = 10, b = 50;
// int num = a + (rand() % (b - a + 1));
// std::cout << "Número entre " << a << " y " << b << ": " << num << std::endl;

// si quieres entre 0 y 1:
// float num = (float)rand() / RAND_MAX