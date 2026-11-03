/**
* Universidad de La Laguna  
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática Asignatura: Algoritmos y Estructuras de Datos Avanzadas
* Curso: 2º Práctica 03: Calculadora para números grandes                                         
* Autor: Luis Eduardo Martín Hernández                                                                                  
* Correo: alu0101631134@ull.edu.es                                                                                      
* Fecha: 11/03/2025                                                                                                    
* Archivo tools.h:                                                                                                      
* Implementación de las funciones necesarias para el main                                                                                
* Referencias:                                                                                                          
* Historial de Revisiones:                                                                                              
*/   

#ifndef TOOLS_H
#define TOOLS_H


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <queue>
#include <stack>

#include "big_number.h"

template <unsigned char Base>
BigNumber<Base>* RPN(std::map<std::string, BigNumber<Base>*> operands, std::queue<std::string> operation) {
  std::stack<BigNumber<Base>*> op_stack;

  while (!operation.empty()) {
    std::string op = operation.front(); 
    operation.pop();

    if (operands.find(op) != operands.end()) {
      op_stack.push(operands[op]);
    } else {
      if (op_stack.size() < 2) {
        throw BigNumberUnknownException();
      }
      BigNumber<Base>* a = op_stack.top(); op_stack.pop();
      BigNumber<Base>* b = op_stack.top(); op_stack.pop();

      switch(op[0]) {
        case '+': op_stack.push((a->add(*b)).copy()); break;
        case '-': op_stack.push((a->subtract(*b)).copy()); break;
        case '*': op_stack.push((a->multiply(*b)).copy()); break;
        case '/': op_stack.push((a->divide(*b)).copy()); break;
      }
    }
  }
  if (op_stack.size() != 1) {
    throw BigNumberUnknownException();
  }
  return op_stack.top();
}


template <unsigned char Base>
void result(std::ifstream& filein, std::ofstream& fileout) {
  std::map<std::string, BigNumber<Base>*> operands;
  std::string line, operation;
	fileout << "Base = " << static_cast<int>(Base) << std::endl;
  while (std::getline(filein, line)) {
    std::istringstream iss(line);
    std::string label, number;
    char equal;
    iss >> label >> equal;
    if (equal == '?') {
			operation = line;
			std::queue<std::string> rpn_queue;
			std::istringstream iss(operation);
			std::string label, op;
			char question;
			iss >> label >> question;
			while (iss >> op) {
				rpn_queue.push(op);
  		}
			BigNumber<Base>* result = RPN(operands, rpn_queue);
			operands[label] = result;
			fileout << label << " = " << *result << std::endl;
    } else {
			iss >> number;
   		operands[label] = BigNumber<Base>::create(number);
			fileout << label << " = " << number << std::endl;
		}
  }
}



#endif