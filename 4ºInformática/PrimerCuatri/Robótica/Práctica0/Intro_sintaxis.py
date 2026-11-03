import sys
from functools import reduce

temperaturas = [22, 27, 19, 31, 25, 18, 30, 24, 28, 33, 21, 26, 17, 29, 35, 23, 25, 32, 20, 27,
                16, 34, 28, 22, 31, 24, 26, 19, 30, 36, 21, 25, 29, 18, 33, 27, 23, 32, 20, 28]

# =====================================================================
# EJERCICIO 1
# =====================================================================
print("=" * 50)
print("EJERCICIO 1")
print("=" * 50)

# 1. Primera y última temperatura (indexación y slicing)
print("\n--- 1.1 Primera y última temperatura ---")
print("Primera temperatura:", temperaturas[0])
print("Última temperatura:", temperaturas[-1])
print("Antepenúltima temperatura:", temperaturas[-3])
print("Tres primeras:", temperaturas[:3])
print("Tres últimas:", temperaturas[-3:])
print("Todas excepto la primera:", temperaturas[1:])

# 2. Recorriendo todas las temperaturas
print("\n--- 1.2 Recorriendo todas las temperaturas ---")
for t in temperaturas:
    print(t)

# 3. Clasificando cada valor
print("\n--- 1.3 Clasificando cada valor ---")
for t in temperaturas:
    if t > 25:
        print(t, "-> alta")
    else:
        print(t, "-> normal")

# 4. Creando una nueva lista
print("\n--- 1.4 Creando una nueva lista ---")
altas = []
for t in temperaturas:
    if t > 25:
        altas.append(t)
print("Temperaturas altas:", altas)

# 5. Detectando una alerta
print("\n--- 1.5 Detectando una alerta ---")
for t in temperaturas:
    if t > 30:
        print("¡ALERTA! Temperatura superior a 30 grados:", t)
        break  # deja de buscar

# 6. Bonus: temperaturas introducidas por el usuario
print("\n--- 1.6 Bonus: temperaturas del usuario ---")
entrada = input("Introduce temperaturas separadas por espacios: ")
temperaturas_usuario = []
for valor in entrada.split():
    temperaturas_usuario.append(int(valor))
print("Lista introducida:", temperaturas_usuario)

# Aplicamos lo anterior a la lista del usuario
altas_usuario = []
for t in temperaturas_usuario:
    if t > 25:
        print(t, "-> alta")
        altas_usuario.append(t)
    else:
        print(t, "-> normal")
print("Temperaturas altas del usuario:", altas_usuario)
for t in temperaturas_usuario:
    if t > 30:
        print("¡ALERTA! Temperatura superior a 30 grados:", t)
        break

# =====================================================================
# EJERCICIO 2 (trabaja con la lista predefinida)
# =====================================================================
print("\n" + "=" * 50)
print("EJERCICIO 2")
print("=" * 50)


# 1. Funciones
def contar_superiores(lista, limite=25):
    """Devuelve cuántas temperaturas de la lista superan el límite."""
    contador = 0
    for t in lista:
        if t > limite:
            contador += 1
    return contador


print("\n--- 2.1 Funciones ---")
if len(sys.argv) > 1:
    limite = int(sys.argv[1])  # límite pasado como argumento
    print(f"Superan {limite} grados:", contar_superiores(temperaturas, limite))
else:
    print("Superan 25 grados (límite por defecto):", contar_superiores(temperaturas))

# 2. Modificación de listas
print("\n--- 2.2 Modificación de listas ---")
temperaturas.append(24)     # añade 24 al final
temperaturas.insert(2, 20)  # inserta 20 en la posición 2
print("Lista modificada:", temperaturas)

# 3. Métodos de listas
print("\n--- 2.3 Métodos de listas ---")
temperaturas.sort(reverse=True)  # de mayor a menor
print("Ordenadas de mayor a menor:", temperaturas)
print("Veces que aparece el 25:", temperaturas.count(25))

# 4. Filtrado y acumulación
print("\n--- 2.4 Filtrado y acumulación ---")
mayores_25 = list(filter(lambda t: t > 25, temperaturas))
print("Temperaturas mayores de 25 (filter):", mayores_25)
suma = reduce(lambda a, b: a + b, temperaturas)
print("Suma de todas las temperaturas (reduce):", suma)