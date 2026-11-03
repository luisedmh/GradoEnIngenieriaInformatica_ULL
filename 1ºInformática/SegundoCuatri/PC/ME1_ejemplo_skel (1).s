# Principio de Computadores. Preparación para el Microexamen
# Operaciones con funciones y direccionamiento indirecto
# Autor: 
# Fecha última modificación: 
#include <iostream>

# const int n1 = 10;
# double v1[n1] = {10.5, 9.5, 7.25, 6.25, 5.75, 4.5, 4.25, 3.5, -1.5, -2.0};
# const int n2 = 5;
# double v2[n2] = {5.5, 4.5, 4.25, 2.5, 2.5 };
# const int n3 = 4;
# double v3[n3] = {7.0, 5.0, 2.0, 1.0};

sizeD = 8
LF = 10
SPACE = 32

    .data
n1:     .word 10
v1:     .double 10.5, 9.5, 7.25, 6.25, 5.75, 4.5, 4.25, 3.5, -1.5, -2.0
n2:     .word 5
v2:     .double 5.5, 4.5, 4.25, 2.5, 2.5
n3:     .word 4
v3:     .double 7.0, 5.0, 2.0, 1.0
cad1:   .asciiz "\nVector con dimension "
cad2:   .asciiz "\nIntentando mezcla con dos vectores ...\n"
cad3:   .asciiz "\nFIN DEL PROGRAMA\n"

    .text

# void printvec(double *v, const int n) {
#     for (int i = 0; i < n; i++)
#         std::cout << v[i] << " ";
    
#     std::cout << "\n";
#     return;
# }


# int ordenado(double *v, const int n) {
#     int resultado = 1;
#     int i = 0;
#     while (i < n-1) {
#         if (v[i+1] >= v[i]) {
#             resultado = 0;
#             break;
#         }
#         i++;
#     }
#     return(resultado);
# }

# void merge(double *v1, const int n1,double *v2, const int n2) {
#     int  o1 = ordenado(v1,n1);
#     if (o1 == 0) return;
#     int o2 = ordenado(v2,n2);
#     if (o2 == 0) return;
#     int i = 0; // índice para recorrer el v1
#     int j = 0; // índice para recorrer el v2
#     while ( ( i < n1) && (j < n2) ) {
#         if (v1[i] >= v2[j]) {
#             std::cout << v1[i] << " ";
#             i++;
#         }
#         else {
#             std::cout << v2[j] << " ";
#             j++;
#         }
#     }
#     while ( i < n1) {
#         std::cout << v1[i] << " ";
#         i++;
#     }
#     while ( j < n2) {
#         std::cout << v2[j] << " ";
#         j++;
#     }
#     std::cout << "\n";
#     return;
# }

# int main(void) {
#     std::cout << "\nVector con dimension " << n1 << std::endl;
#     printvec(v1,n1);
  
#     std::cout << "\nVector con dimension " << n2 << std::endl;
#     printvec(v2,n2);
  
#     std::cout << "\nVector con dimension " << n3 << std::endl;
#     printvec(v3,n3);
  
#     std::cout << "\nIntentando mezcla con dos vectores ...\n";
#     merge(v1,n1,v2,n2);
#     std::cout << "\nIntentando mezcla con dos vectores ...\n";
#     merge(v1,n1,v3,n3);

#     std::cout << "\nFIN DEL PROGRAMA\n";
#     return(0);
# }


# void printvec(double *v, const int n) {
# Esta función llama a otra -> necesita pila
# v -> a0 -> s4
# n -> a1 -> s5
# i -> s6

printvec:
	# PUSH s4, s5, s6, ra: 4 * 4 = 16
	addi	$sp, $sp, -16
	sw	$s4, 0($sp)
	sw	$s5, 4($sp)
	sw	$s6, 8($sp)
	sw	$ra, 12($sp)
	
	# Copiamos parámetros de entrada en salvado
	move	$s4, $a0
	move	$s5, $a1
	
#     for (int i = 0; i < n; i++)
	move	$s6, $zero
printvec_for:
	bge	$s6,$s5,printvec_for_fin
#         std::cout << v[i] << " ";
	# v[i]
	mul	$t0, $s6, sizeD
	addu	$t0, $t0, $s4
	l.d	$f4, 0($t0)
#       << v[i]
	li	$v0, 3
	mov.d	$f12, $f4
	syscall
#	<< " ";
	li	$v0, 11
	li	$a0, ' '
	syscall
		
	addi	$s6,1		#i++
	b	printvec_for:
pritvec_for_fin:    
#     std::cout << "\n";

#     return;
# }
	# POP 
	lw	$s4, 0($sp)
	lw	$s5, 4($sp)
	lw	$s6, 8($sp)
	lw	$ra, 12($sp)
	addi	$sp, $sp, 16
	
	jr	$ra
printvec_fin:

# int ordenado(double *v, const int n) {
# Esta función no necesita pila
# v → a0
# n → a1
# Parámetro de salida entero → v0 (resultado) 
# resultado → v0
# i → t4
#     int resultado = 1;
#     int i = 0;
#     while (i < n-1) {
#         if (v[i+1] >= v[i]) {
#             resultado = 0;
#             break;
#         }
#         i++;
#     }
#     return(resultado);
# }



# void merge(double *v1, const int n1,double *v2, const int n2) {
# Funcion que llama a otra necesita pila
# v1 → a0 → s0
# n1 → a1 → s1
# v2 → a2 → s2
# n2 → a3 → s3

# o1 → t0
# o2 → t1

# i → s4
# j → s5

merge:
	#PUSH ra, s0, s1, s2, s3, s4, s5: 7 * 4 = 28
	
	# PUSH ra, s0, s1, f20.d, f22.d: 4 * 3 + 8 * 2 = 28
	
	addi	$sp, $sp, -28
	sw	$ra,0($sp)
	sw	$s0,4($sp)
	sw	$s1,8($sp)
	s.d	$f20,12($sp)
	s.d	$f22,20($sp)
	
#     int  o1 = ordenado(v1,n1);
#     if (o1 == 0) return;
#     int o2 = ordenado(v2,n2);
#     if (o2 == 0) return;
#     int i = 0; // índice para recorrer el v1
#     int j = 0; // índice para recorrer el v2
#     while ( ( i < n1) && (j < n2) ) {
#         if (v1[i] >= v2[j]) {
#             std::cout << v1[i] << " ";
#             i++;
#         }
#         else {
#             std::cout << v2[j] << " ";
#             j++;
#         }
#     }
#     while ( i < n1) {
#         std::cout << v1[i] << " ";
#         i++;
#     }
#     while ( j < n2) {
#         std::cout << v2[j] << " ";
#         j++;
#     }
#     std::cout << "\n";
#     return;
# }
