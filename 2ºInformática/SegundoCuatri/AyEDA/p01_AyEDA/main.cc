/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática* Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º* Práctica 01: Representación de números grandes                                          
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 11/02/2025                                                                                                    
* Archivo main.cc:                                                                                                      
* Función principal del programa                                                                                  
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/   

#include "big_unsigned.h"
#include "big_integer.h"

int main() {
    BigInteger x, y;
    std::cin >> x >> y;
    std::cout << "El resultado del mcd(" << x << ", " << y << ") es: ";
    BigInteger result = mcd(x, y);
    std::cout << result << std::endl;
    return 0; 
}