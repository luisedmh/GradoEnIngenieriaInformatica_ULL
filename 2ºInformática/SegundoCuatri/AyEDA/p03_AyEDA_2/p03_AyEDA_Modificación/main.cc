/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º Práctica 03: Calculadora para números grandes                                         
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 11/03/2025                                                                                                    
* Archivo main.cc:                                                                                                      
* Implementación de la función principal o main                                                                                 
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/   

#include "big_unsigned.h"
#include "big_integer.h"
#include "big_rational.h"
#include "tools.h"
#include "big_number.h"
#include "big_number_exceptions.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Uso: " << argv[0] << " <archivo_entrada> <archivo_salida>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "Error abriendo el archivo de entrada.\n";
        return 1;
    }

    std::ofstream output(argv[2]);
    if (!output) {
        std::cerr << "Error abriendo el archivo de salida.\n";
        return 1;
    }
    try {
        std::string str;
        std::getline(input, str); 
        std::istringstream iss(str);
        std::string label;
        char equal;
        int base;
        iss >> label >> equal >> base;
        if (label != "Base" || equal != '=') {
            std::cerr << "Formato de entrada incorrecto" << std::endl;
            return 1;
        }

        switch(base) {
            case 2: 
              result<2>(input, output);
              break;
            case 8: 
              result<8>(input, output);
              break;
            case 10: 
              result<10>(input, output);
              break;   
            case 16: 
              result<16>(input, output);
              break;
            default:
              std::cerr << "Base no válida" << std::endl;
              return 1;
          }
        
    } catch (const BigNumberBadDigit& e) {
        std::cerr << "Excepción atrapada: " << e.what() << std::endl;
        output << "Error en la entrada: número con dígitos inválidos\n";
    } catch (const BigNumberDivisionByZero& e) {
        std::cerr << "Excepción atrapada: " << e.what() << std::endl;
        output << "Error en la entrada: división por cero\n";
    } catch (const BigNumberEntryError& e) {
        std::cerr << "Excepción atrapada: " << e.what() << std::endl;
        output << "Error en la entrada\n";
    } catch (const BigNumberUnknownException& e) {
        std::cerr << "Excepción atrapada: " << e.what() << std::endl;
        output << "Error desconocido\n";
    } catch (const BigNumberRationalModule& e) {
        std::cerr << "Excepción atrapada: " << e.what() << std::endl;
        output << "Error en el módulo racional\n";
    } catch (const std::exception& e) {
        std::cerr << "Error inesperado: " << e.what() << std::endl;
        return 1;
    }

    input.close();
    output.close();

    return 0;
}
