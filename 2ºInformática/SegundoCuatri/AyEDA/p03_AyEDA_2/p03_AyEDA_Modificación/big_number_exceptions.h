/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º Práctica 03: Calculadora para números grandes                                         
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 11/03/2025                                                                                                    
* Archivo big_number_exceptions.h:                                                                                                      
* Declaración de las clases de errores                                                                                 
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/   

#ifndef BIG_NUMBER_EXCEPTIONS_H
#define BIG_NUMBER_EXCEPTIONS_H

#include <exception>
#include <string>

class BigNumberException : public std::exception {
 public:
    explicit BigNumberException(const std::string& msg) : message_(msg) {}
    virtual const char* what() const noexcept override { return message_.c_str(); }

 private:
    std::string message_;
};

class BigNumberBadDigit : public BigNumberException {
 public:
    explicit BigNumberBadDigit(const std::string& msg = "Error: Dígito no válido en la entrada")
        : BigNumberException(msg) {}
};

class BigNumberDivisionByZero : public BigNumberException {
 public:
    explicit BigNumberDivisionByZero(const std::string& msg = "Error: División por cero")
        : BigNumberException(msg) {}
};

class BigNumberEntryError : public BigNumberException {
    public:
       explicit BigNumberEntryError(const std::string& msg = "Error: Entrada incorrecta")
           : BigNumberException(msg) {}
};

class BigNumberUnknownException : public BigNumberException {
   public:
      explicit BigNumberUnknownException(const std::string& msg = "Error: Desconocido")
          : BigNumberException(msg) {}
};

class BigNumberRationalModule : public BigNumberException {
   public:
      explicit BigNumberRationalModule(const std::string& msg = "Error: Intento de calcular módulo desde un racional")
          : BigNumberException(msg) {}
};

#endif
