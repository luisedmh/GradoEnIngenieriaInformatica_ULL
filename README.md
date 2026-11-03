# Grado en Ingeniería Informática — Universidad de La Laguna (ULL)

![Universidad](https://img.shields.io/badge/Universidad-ULL-5c2d91)
![Erasmus](https://img.shields.io/badge/Erasmus-Linnaeus%20University%20🇸🇪-006aa7)
![Lenguajes](https://img.shields.io/badge/C%2B%2B%20·%20C%20·%20CUDA%20·%20Python%20·%20Verilog%20·%20MIPS%20·%20Bash%20·%20Ruby%20·%20Prolog-informational)
![Estado](https://img.shields.io/badge/Estado-En%20curso-brightgreen)

Este repositorio reúne **las prácticas, tareas, informes y proyectos que he realizado a lo largo del Grado en Ingeniería Informática en la Universidad de La Laguna**, organizados por curso y cuatrimestre. Es, en cierto modo, un recorrido por mi formación: desde los primeros programas en ensamblador MIPS de primero hasta mi Trabajo de Fin de Grado sobre simulación de fluidos heterogénea CPU+GPU en CUDA.

Además, el **segundo cuatrimestre de 3º lo cursé de Erasmus en Suecia, en la [Linnaeus University (LNU)](https://lnu.se/en/)**, por lo que esa parte del repositorio contiene asignaturas impartidas en inglés y con un enfoque distinto al de la ULL.

> No están todas las asignaturas de la carrera: aquí he subido **todo lo que he conseguido recuperar** de mis entregas. Algunas asignaturas tienen el código completo y otras solo los informes o la documentación.

---

## Índice

- [Estructura del repositorio](#-estructura-del-repositorio)
- [1º curso](#1º-curso)
- [2º curso](#2º-curso)
- [3º curso](#3º-curso)
  - [🇸🇪 Erasmus en la Linnaeus University (Suecia)](#-erasmus-en-la-linnaeus-university-suecia)
- [4º curso](#4º-curso)
  - [⭐ Trabajo de Fin de Grado](#-trabajo-de-fin-de-grado-tfg)
- [Tecnologías y lenguajes](#-tecnologías-y-lenguajes)
- [Cómo compilar y ejecutar las prácticas](#-cómo-compilar-y-ejecutar-las-prácticas)
- [Aviso sobre integridad académica](#-aviso-sobre-integridad-académica)
- [Contacto](#-contacto)

---

## Estructura del repositorio

```
GradoEnIngenieriaInformatica_ULL/
├── 1ºInformática/
│   └── SegundoCuatri/        → PC, SED
├── 2ºInformática/
│   ├── PrimerCuatri/         → CyA, EC, SSOO
│   └── SegundoCuatri/        → AyEDA, RSD
├── 3ºInformática/
│   ├── PrimerCuatri/         → Bases de Datos, GPI, IA, LPP
│   └── SegundoCuatri/        → 🇸🇪 Erasmus LNU: Admin, Internet Security,
│                               Software Architectures, Web Management
└── 4ºInformática/
    ├── PrimerCuatri/         → GCO, Robótica, Sistemas
    └── SegundoCuatri/        → TFG
```

| Curso | Cuatrimestre | Asignaturas | Lugar |
|:----:|:-----------:|-------------|:-----:|
| 1º | 2º | Principios de Computadores · Sistemas Electrónicos Digitales | 🇪🇸 ULL |
| 2º | 1º | Computabilidad y Algoritmia · Estructura de Computadores · Sistemas Operativos | 🇪🇸 ULL |
| 2º | 2º | Algoritmos y Estructuras de Datos Avanzadas · Redes y Sistemas Distribuidos | 🇪🇸 ULL |
| 3º | 1º | Bases de Datos · Gestión de Proyectos Informáticos · Inteligencia Artificial · Lenguajes y Paradigmas de Programación | 🇪🇸 ULL |
| 3º | 2º | Systems Administration · Internet Security · Software Architectures · Web Management | 🇸🇪 **LNU (Erasmus)** |
| 4º | 1º | Gestión del Conocimiento en las Organizaciones · Robótica · Sistemas | 🇪🇸 ULL |
| 4º | 2º | **Trabajo de Fin de Grado** | 🇪🇸 ULL |

---

## 1º curso

### Segundo cuatrimestre

#### Principios de Computadores (PC) — [`PC`](1ºInformática/SegundoCuatri/PC)
Introducción a la arquitectura de computadores a bajo nivel mediante **ensamblador MIPS**.
- Programa de preparación del microexamen: operaciones con **funciones**, paso de parámetros, uso de la pila y **direccionamiento indirecto** sobre vectores de números en coma flotante (`double`).
- Traducción manual de código C++ a ensamblador, gestión de registros y llamadas al sistema.

**Tecnologías:** MIPS Assembly, simulador MARS/QtSpim.

#### Sistemas Electrónicos Digitales (SED) — [`SED`](1ºInformática/SegundoCuatri/SED)
- Tarea 1 en formato PDF sobre fundamentos de electrónica digital.

---

## 2º curso

### Primer cuatrimestre

#### Computabilidad y Algoritmia (CyA) — [`CyA`](2ºInformática/PrimerCuatri/CyA)
Una de las asignaturas con más código del repositorio. Todas las prácticas están implementadas en **C++** siguiendo la guía de estilo de Google, con diseño orientado a objetos y `makefile` propio.

| Práctica | Contenido |
|---------|-----------|
| **P02 – Strings** | Clases `Alphabet`, `String` y `Language`: operaciones sobre cadenas y lenguajes formales (alfabeto, longitud, inversa, prefijos, sufijos…). |
| **P03** | Informe en PDF. |
| **P04 – Code Analyzer** | Analizador de código fuente C++ mediante **expresiones regulares**: detecta variables, bucles, comentarios y la función `main`. Incluye la versión con la modificación realizada en el laboratorio. |
| **P05** | Informe en PDF. |
| **P06 – Automata Simulator** | **Simulador de autómatas finitos** (NFA/DFA): lectura del autómata desde fichero, clases `State`, `Alphabet` y `Automaton`, y comprobación de aceptación de cadenas. |
| **P07** | Informe en PDF. |
| **P08 – Grammar to CNF** | Transformación de una **gramática independiente del contexto a Forma Normal de Chomsky**, con ficheros de entrada/salida `.gra`. |
| **P09** | Informe en PDF. |
| **P11** | Algoritmo voraz sobre **conjuntos de puntos**: construcción de un árbol de expansión mínima (EMST) y exportación a **Graphviz (`.dot`)**. |
| **P12 – Convex Hull** | Cálculo de la **envolvente convexa** (*Quickhull*) de un conjunto de puntos, con salida gráfica en `.dot`/PDF. |

#### Estructura de Computadores (EC) — [`EC`](2ºInformática/PrimerCuatri/EC)
Diseño de hardware digital con **Verilog**, simulado con Icarus Verilog y visualizado con GTKWave (ficheros `.vcd`).
- Sumador completo (`fa`), sumadores de 4 bits (`sum4`, `sum4_v2`), multiplexores (`mux2_4`, `mux4_1`), complemento a 1 (`compl1`), unidad lógica (`ul4`), módulo de preprocesado y ensamblado final de una **ALU**.
- Cada módulo tiene su **testbench** (`*_tb.v`) correspondiente.

#### Sistemas Operativos (SSOO) — [`SSOO`](2ºInformática/PrimerCuatri/SSOO)
- **Práctica 2 – `docserver`:** servidor de documentos en **C++ sobre la API de sistemas POSIX/Linux**, desarrollado de forma incremental (puntos 1 a 4 y sus modificaciones). Uso de *sockets*, gestión segura de descriptores de fichero con RAII (`SafeFD`), proyección de ficheros en memoria (`SafeMap` / `mmap`) y manejo de errores con `std::expected`.
- Scripts de apoyo para el estudio de la teoría.

### Segundo cuatrimestre

#### Algoritmos y Estructuras de Datos Avanzadas (AyEDA) — [`AyEDA`](2ºInformática/SegundoCuatri/AyEDA)
Prácticas en **C++ con uso intensivo de plantillas, herencia y polimorfismo**.

| Práctica | Contenido |
|---------|-----------|
| **P01** | `BigUnsigned` y `BigInteger`: aritmética de **enteros de precisión arbitraria** (suma, resta, multiplicación, división, MCD). Incluye la modificación con `BigRational`. |
| **P02** | Generalización con **plantillas** (`BigUnsigned<Base>`) para trabajar en distintas bases numéricas. |
| **P03** | Jerarquía abstracta `BigNumber` con `BigUnsigned`, `BigInteger` y `BigRational`, operaciones polimórficas y **excepciones propias**. |
| **P04** | **Tablas hash**: funciones de dispersión y exploración. |
| **P05** | **Algoritmos de ordenación** genéricos sobre secuencias de claves (`NIF`): Inserción, ShakeSort, QuickSort, HeapSort y ShellSort, con jerarquía `SortMethod`. |
| **P06** | **Árboles binarios**: árbol binario equilibrado (`AB`), árbol binario de búsqueda (`ABB`) y **árboles AVL** con rotaciones. Incluye versión modificada. |

#### Redes y Sistemas Distribuidos (RSD) — [`RSD`](2ºInformática/SegundoCuatri/RSD)
Prácticas realizadas en pareja.
- **Análisis de protocolos** de red con Wireshark (informe).
- Informes de las **Prácticas 2 y 3**.
- Práctica de **programación con sockets** (`sockets2425-pe104-9`).

---

## 3º curso

### Primer cuatrimestre (ULL)

#### Bases de Datos (BD) — [`BASE DE DATOS`](3ºInformática/PrimerCuatri/BASE%20DE%20DATOS)
Informes de las prácticas de **SQL**:

| Práctica | Contenido |
|---------|-----------|
| **P4** | Consultas elementales |
| **P5** | Consultas con múltiples tablas (*joins*) |
| **P6** | Consultas avanzadas (subconsultas, agrupaciones…) |
| **P7** | Control de transacciones |
| **P8** | Definición de datos (DDL: creación de tablas, restricciones) |

#### Gestión de Proyectos Informáticos (GPI) — [`GPI`](3ºInformática/PrimerCuatri/GPI)
Trabajo en equipo (Equipo 8, curso 2025-2026):
- **Plan de Dirección del Proyecto (PDP)**.
- **Análisis Coste-Beneficio / planificación (ACP)**.
- Planificación temporal del proyecto con diagramas de Gantt y PERT (`.pod`, OpenProj/ProjectLibre).

#### Inteligencia Artificial (IA) — [`IA`](3ºInformática/PrimerCuatri/IA)

| Práctica | Contenido |
|---------|-----------|
| **P01 – Búsqueda no informada** | Búsqueda en **amplitud (BFS)** y **profundidad (DFS)** sobre grafos leídos desde fichero, en C++, con generación del árbol de búsqueda e informe de nodos generados/inspeccionados. |
| **P02 – Búsqueda informada** | Algoritmo **A\*** para encontrar el camino óptimo en un **laberinto**, con heurísticas (Manhattan/Euclídea) y modificaciones realizadas en el laboratorio. |
| **P04 – Prolog** | Ejercicios de **programación lógica** en Prolog. |
| **P05 – Clustering** | **K-Means** y métodos basados en prototipos sobre el dataset **Iris**, en un *notebook* de Jupyter (Python, scikit-learn). |

#### Lenguajes y Paradigmas de Programación (LPP) — [`LPP`](3ºInformática/PrimerCuatri/LPP)
- Proyecto **Ruby** (`Sanitarios_Ruby`) desarrollado con TDD, gemas y programación orientada a objetos/funcional.
- Ejercicios sobre la resolución de constantes en Ruby (módulos, herencia y ámbito léxico).

---

### 🇸🇪 Erasmus en la Linnaeus University (Suecia)

**Segundo cuatrimestre de 3º — curso 2025-2026**

El segundo cuatrimestre de tercero lo realicé como **estudiante de intercambio Erasmus+ en la [Linnaeus University (Linnéuniversitetet, LNU)](https://lnu.se/en/)**, en Suecia. Fue una de las experiencias más enriquecedoras de la carrera, tanto a nivel académico como personal:

- **Todas las asignaturas en inglés**: clases, informes, presentaciones y exámenes.
- Metodología basada en **assignments** individuales con informes técnicos extensos, defensas y presentaciones en vídeo.
- Uso de infraestructura cloud propia de la universidad para las prácticas de administración de sistemas.

Las asignaturas que cursé en la LNU fueron:

#### Systems Administration & Virtualization — [`Admin`](3ºInformática/SegundoCuatri/Admin)
- **Assignment 1 – Bash scripting:** batería de scripts de administración:
  - `cli.bash` / `cli_improved.bash`: interfaz de línea de comandos interactiva.
  - `backup.bash`: copias de seguridad automatizadas.
  - `analyse.bash`: análisis del sistema.
  - `large_files.bash`: localización de ficheros de gran tamaño.
- **Assignments 2 y 3:** administración de máquinas Linux virtualizadas en la nube (OpenStack), servicios, usuarios y configuración.
- Guion de vídeo sobre *Systems Administration & Virtualization*.

#### Internet Security — [`InternetSecurity`](3ºInformática/SegundoCuatri/InternetSecurity)
Asignatura práctica de seguridad en redes y criptografía aplicada:
- **Pre-assignment** y **Assignment 1:** fundamentos de seguridad en Internet.
- **Assignment 2 – Correo seguro y PGP/GPG:** generación de pares de claves, intercambio de claves públicas con compañeros, **cifrado y firma digital** de ficheros y correos, verificación de firmas y análisis de cabeceras de correos (`.eml`), incluido el envío de mensajes anónimos/suplantados.
- **Assignment 3:** criptografía y gestión de claves.
- **Assignment 4 – TLS/HTTPS:** creación de una **autoridad/certificado autofirmado con OpenSSL** (`req.conf`), configuración de un servidor HTTPS y captura y análisis del tráfico HTTP frente a HTTPS (`.pcap`).

#### Software Architectures — [`SoftwareArchitectures`](3ºInformática/SegundoCuatri/SoftwareArchitectures)
- Assignments sobre **patrones y estilos arquitectónicos**, atributos de calidad y documentación de arquitecturas software.
- Material de estudio y guion de presentación.

---

## 4º curso

### Primer cuatrimestre

#### Gestión del Conocimiento en las Organizaciones (GCO) — [`GCO`](4ºInformática/PrimerCuatri/GCO)
- Implementación en **Python** de un **sistema de recomendación por filtrado colaborativo**: cálculo de medias, métricas de similitud entre usuarios (correlación de Pearson, distancia coseno…) y predicción de valoraciones.

#### Robótica — [`Robótica`](4ºInformática/PrimerCuatri/Robótica)
Prácticas en **Python** sobre **cinemática de manipuladores robóticos**:
- **Práctica 0:** introducción a la sintaxis de Python.
- **Prácticas 1–3:** **cinemática directa** de manipuladores de distinto número de articulaciones (rotacionales y prismáticas) usando los **parámetros de Denavit-Hartenberg**, con apuntes propios del procedimiento.

#### Sistemas y Tecnologías Web — [`Sistemas`](4ºInformática/PrimerCuatri/Sistemas)
- Práctica 4, ejercicio 7.
- **Proyecto `gpu-grid`**.

### Segundo cuatrimestre

#### Trabajo de Fin de Grado (TFG) — [`TFG`](4ºInformática/SegundoCuatri/TFG)

## **LBM heterogéneo CPU+GPU con reequilibrio dinámico y auto-calibración**
https://github.com/luisedmh/lbm-heterogeneous-autotuning.git

Mi TFG consiste en un **simulador de dinámica de fluidos computacional (CFD) basado en el método de Lattice Boltzmann (LBM, modelo D2Q9)** capaz de **repartir el dominio de simulación entre CPU y GPU en tiempo de ejecución**, reajustando el reparto según el rendimiento medido en vivo en lugar de fijarlo al inicio.

**Motivación:** la mayoría de trabajos de *autotuning* en cómputo tipo *stencil* deciden el reparto CPU/GPU (o la precisión numérica) una sola vez al principio. Este proyecto explora qué ocurre si esa decisión se reajusta **mientras la simulación corre**, a partir de medidas reales.

**Evolución del proyecto:**

| Fase | Contenido |
|------|-----------|
| 1 | Solver LBM D2Q9 secuencial en CPU |
| 2 | Paralelización en CPU con **OpenMP** |
| 3 | Solver en GPU con **CUDA** (colisión BGK + *streaming* fusionados en un único kernel) |
| 4 | Ejecución heterogénea CPU (OpenMP) + GPU (CUDA) con reparto fijo |
| 5 | Solver 3D en GPU |
| 6 | **Reequilibrio dinámico** del reparto CPU/GPU durante la ejecución |
| 7 | **Auto-calibración**: el sistema decide por sí mismo, midiendo, si compensa usar la CPU |

**Resultados destacados:**
- El solver solo-GPU se comparó en igualdad de condiciones (mismo tamaño de problema y precisión) con **FluidX3D**, uno de los LBM en GPU más rápidos disponibles públicamente, alcanzando **~7341 MLUPS, un ~39 % más en FP32**.
- En **FP64**, el reparto dinámico CPU+GPU consigue **entre un +24,7 % y un +31,3 %** de rendimiento sobre la GPU sola, convergiendo automáticamente al reparto óptimo sin conocerlo de antemano.
- En FP32, donde la CPU no aporta ganancia real en el hardware de pruebas, el sistema **detecta por sí solo que no compensa y no usa la CPU**, evitando regresiones.
- Todas las versiones se **validaron celda a celda** frente a una implementación de referencia ya verificada.

La carpeta incluye el código del solver, la *suite* de **benchmarks de rendimiento** (configuraciones, *runner*, resultados y gráficas), y la documentación detallada de cada etapa.

**Tecnologías:** C++, **CUDA**, **OpenMP**, Python (benchmarks y gráficas), Make.

---

## Tecnologías y lenguajes

| Área | Tecnologías |
|------|-------------|
| **Lenguajes** | C++ (11/17/20/23), C, CUDA, Python, Bash, Ruby, Prolog, SQL, Verilog, ensamblador MIPS |
| **HPC / paralelismo** | CUDA, OpenMP, benchmarking (MLUPS), profiling |
| **Sistemas** | Linux, API POSIX, sockets, `mmap`, virtualización, OpenStack |
| **Seguridad** | GPG/PGP, OpenSSL, certificados X.509, TLS/HTTPS, Wireshark |
| **IA y datos** | Algoritmos de búsqueda (BFS, DFS, A\*), K-Means, Jupyter, scikit-learn, sistemas de recomendación |
| **Hardware** | Verilog, Icarus Verilog, GTKWave |
| **Herramientas** | Git, Make, VS Code, Graphviz, LaTeX, ProjectLibre |

---

## Cómo compilar y ejecutar las prácticas

La mayoría de las prácticas en C++ incluyen su propio `makefile`:

```bash
git clone https://github.com/luisedmh/GradoEnIngenieriaInformatica_ULL.git
cd GradoEnIngenieriaInformatica_ULL/2ºInformática/SegundoCuatri/AyEDA/p05_AyEDA
make
./<ejecutable> [argumentos]
```

Para los módulos de **Verilog**:

```bash
iverilog -o alu alu.v alu_tb.v
vvp alu
gtkwave alu.vcd
```

Para el **TFG** se necesita `g++` con soporte OpenMP y, opcionalmente, `nvcc` (CUDA Toolkit) para el backend de GPU:

```bash
make        # detecta automáticamente si hay CUDA disponible
make run
```

---

## Aviso sobre integridad académica

Este repositorio se publica con fines **de portfolio y de consulta**. Si eres estudiante de la ULL (o de la LNU) y estás cursando alguna de estas asignaturas, úsalo como referencia para entender los conceptos, **no para copiar las entregas**: además de ir contra las normas académicas, te perderás lo más valioso de cada práctica.

---

## Contacto

**Luis Eduardo Martín Hernández**
- GitHub: [@luisedmh](https://github.com/luisedmh)
- Email: luiseduardomartinhdez@gmail.com

---

<p align="center">
  Hecho en 🇮🇨 Tenerife y 🇸🇪 Suecia · Universidad de La Laguna · Linnaeus University
</p>
