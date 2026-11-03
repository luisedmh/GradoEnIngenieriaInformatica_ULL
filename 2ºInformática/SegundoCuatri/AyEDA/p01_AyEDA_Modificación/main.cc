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
#include "big_rational.h"

int main() {
    BigInteger x, y;
    std::cin >> x >> y;
    std::cout << "El resultado del mcd(" << x << ", " << y << ") es: ";
    BigInteger result = mcd(x, y);
    std::cout << result << std::endl;

    BigInteger a, c;
    BigUnsigned b, d;
    std::cout << "Introduzca un numerador" << std::endl;
    std::cin >> a;
    std::cout << "Introduzca un denominador" << std::endl;
    std::cin >> b;
    std::cout << "Introduzca un numerador" << std::endl;
    std::cin >> c;
    std::cout << "Introduzca un denominador" << std::endl;
    std::cin >> d;
    BigRational operando_1(a, b);
    BigRational operando_2(c, d);
    std::cout << "Los números introducidos son: " << std::endl << operando_1 << std::endl << operando_2 << std::endl;
    BigRational sum_result = operando_1 + operando_2;
    std::cout << "La suma de estos dos operandos es: " << std::endl << sum_result;


    return 0; 
}