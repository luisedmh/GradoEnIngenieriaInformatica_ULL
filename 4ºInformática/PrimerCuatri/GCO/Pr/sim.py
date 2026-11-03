import math

def main():
    personA = [5, 3, 4, 4]
    personB = [4, 3, 4, 3, 5]
    # personB = [3, 1, 2, 3, 3]
    n = 4

    suma = 0
    contador = 0
    for i in range(4):
        if personA[i] != 0:
            suma = suma + personA[i]
    mediaA = suma / 4

    suma = 0
    contador = 0
    for i in range(4):
        if personB[i] != 0:
            suma = suma + personB[i]
    print(suma)
    mediaB = suma / 4

    numerador = 0
    sumaA = 0
    sumaB = 0
    for i in range(n):
        if personA[i] != 0 and personB[i] != 0:
            difA = personA[i] - mediaA
            difB = personB[i] - mediaB
            numerador = numerador + difA * difB
            sumaA = sumaA + difA * difA
            sumaB = sumaB + difB * difB

    sim = numerador / (math.sqrt(sumaA) * math.sqrt(sumaB))

    print("Media PersonA:", mediaA)
    print("Media personB:", mediaB)
    print("sim(PersonA, personB) =", round(sim, 2))

main()