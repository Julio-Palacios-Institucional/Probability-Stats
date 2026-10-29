<<<<<<< HEAD
<<<<<<< HEAD
\# Probabilidad y Estadística · 2026B



Repositorio con las actividades de la materia \*\*Probabilidad y Estadística\*\*: Hands-on, Challenges y Tech Readings. Incluye los programas en C++ de regresión lineal simple (Caso Benetton) y de tabla de frecuencia extendida, además de las derivaciones y hojas de cálculo del curso.



| | |

|---|---|

| \*\*Institución\*\* | TecMM · Unidad Académica Zapopan |

| \*\*Programa\*\* | Ingeniería en Sistemas Computacionales |

| \*\*Docente\*\* | Dr. José Antonio Aviña Méndez |

| \*\*Ciclo\*\* | 2026B |

| \*\*Autor\*\* | Julio Emiliano Palacios Bustamante |



\## Contenido



Cada actividad vive en una carpeta con el mismo nombre que el assignment.



| Carpeta | Tema | Herramienta |

|---|---|---|

| \[Tech Reading 1](./Tech%20Reading%201) | Aplicaciones de Probabilidad y Estadística: Machine Learning, Deep Learning, Data Science, Big Data Analytics, robótica inteligente y UAV | Lectura y análisis |

| \[Hands-on 1](./Hands-on%201) | Regresión lineal simple paso a paso con D = {(1,4), (2,7), (3,10), (4,13), (5,16)}; resultado esperado β₀ = 1, β₁ = 3 | Google Sheets |

| \[Hands-on 2](./Hands-on%202) | Regresión lineal simple paso a paso con D = {(1,6), (2,8), (3,10), (4,12), (5,14)}; resultado esperado β₀ = 4, β₁ = 2 | Google Sheets |

| \[Hands-on 3](./Hands-on%203) | Regresión lineal simple en código con el Caso Benetton (Sales y Advertising) | C++ |

| \[Hands-on 4](./Hands-on%204) | Tabla de frecuencia extendida con 30 o más datos | C++ |

| \[Challenge 1](./Challenge%201) | Derivada parcial del error con respecto a la pendiente, ∂E/∂β₁, paso a paso | Documento |



\*\*Evaluación del curso:\*\* Tech Readings 10 % · Hands-on 70 % · Challenges 20 %.



\## Hands-on 3 · Regresión lineal simple (Caso Benetton)



Implementa el modelo de regresión lineal simple construido en clase para estimar los coeficientes óptimos a partir del dataset del \[Caso Benetton](https://www.displayr.com/what-is-linear-regression/), usando solo las columnas \*\*Sales\*\* (y) y \*\*Advertising\*\* (x).



$$

\\beta\_1 = \\frac{n\\sum xy - \\sum x \\sum y}{n\\sum x^2 - \\left(\\sum x\\right)^2}

\\qquad

\\beta\_0 = \\frac{\\sum y - \\beta\_1 \\sum x}{n}

\\qquad

\\hat{y} = \\beta\_0 + \\beta\_1 x

$$



\- \*\*Entrada:\*\* ninguna. El dataset está declarado directamente en el código.

\- \*\*Salida:\*\* la ecuación de regresión como texto, con β₀ y β₁ calculados por el programa, y las predicciones de Sales para cinco valores de Advertising que no están en el dataset.



```text

Ecuacion: y = \[β0] + \[β1]x



Predicciones de Sales:

&#x20; Advertising = \[x1] -> \[y1]

&#x20; ...

```



\## Hands-on 4 · Tabla de frecuencia extendida



Agrupa en clases un dataset de números reales (30 o más datos, declarado en el código) e imprime la tabla con, en este orden:



1\. Número de clases

2\. Límites de clase

3\. Frecuencia absoluta

4\. Punto medio o marca de clase

5\. Frecuencia relativa

6\. Frecuencia absoluta acumulada

7\. Frecuencia relativa acumulada

8\. Porcentaje



\## Cómo compilar y ejecutar



Requiere un compilador de C++ (por ejemplo, `g++`).



```bash

cd "Hands-on 3"

g++ main.cpp -o hands-on3

./hands-on3          # en Windows: .\\hands-on3.exe

```



El mismo procedimiento aplica a `Hands-on 4`. Si el archivo fuente tiene otro nombre, ajusta el comando.



\## Estructura del repositorio



```text

.

├── README.md

├── Tech Reading 1/

│   └── README.md

├── Hands-on 1/

│   └── README.md

├── Hands-on 2/

│   └── README.md

├── Hands-on 3/

│   └── main.cpp

├── Hands-on 4/

│   └── main.cpp

└── Challenge 1/

│   └── README.md

```



\## Convenciones



\- Una carpeta por assignment, con el nombre exacto del assignment.

\- Solo código fuente: sin ejecutables ni archivos compilados.

\- Los datos van declarados en el código; los programas no piden entradas.



\## Avance



\- \[ ] Tech Reading 1

\- \[ ] Hands-on 1

\- \[ ] Hands-on 2

\- \[ ] Hands-on 3

\- \[ ] Hands-on 4

\- \[ ] Challenge 1



El código se sube después de su evaluación individual, según lo indicado por el docente.



\## Nota de uso



Material académico personal, publicado como evidencia de las actividades del curso. Úsalo como referencia, no como entrega propia.



=======
# Probabilidad y Estadística · 2026B

Repositorio con las actividades de la materia **Probabilidad y Estadística**: Hands-on, Challenges y Tech Readings. Incluye los programas en C++ de regresión lineal simple (Caso Benetton) y de tabla de frecuencia extendida, además de las derivaciones y hojas de cálculo del curso.

| | |
|---|---|
| **Institución** | TecMM · Unidad Académica Zapopan |
| **Programa** | Ingeniería en Sistemas Computacionales |
| **Docente** | Dr. José Antonio Aviña Méndez |
| **Ciclo** | 2026B |
| **Autor** | Julio Emiliano Palacios Bustamante |

## Contenido

Cada actividad vive en una carpeta con el mismo nombre que el assignment.

| Carpeta | Tema | Herramienta |
|---|---|---|
| [Tech Reading 1](./Tech%20Reading%201) | Aplicaciones de Probabilidad y Estadística: Machine Learning, Deep Learning, Data Science, Big Data Analytics, robótica inteligente y UAV | Lectura y análisis |
| [Hands-on 1](./Hands-on%201) | Regresión lineal simple paso a paso con D = {(1,4), (2,7), (3,10), (4,13), (5,16)}; resultado esperado β₀ = 1, β₁ = 3 | Google Sheets |
| [Hands-on 2](./Hands-on%202) | Regresión lineal simple paso a paso con D = {(1,6), (2,8), (3,10), (4,12), (5,14)}; resultado esperado β₀ = 4, β₁ = 2 | Google Sheets |
| [Hands-on 3](./Hands-on%203) | Regresión lineal simple en código con el Caso Benetton (Sales y Advertising) | C++ |
| [Hands-on 4](./Hands-on%204) | Tabla de frecuencia extendida con 30 o más datos | C++ |
| [Challenge 1](./Challenge%201) | Derivada parcial del error con respecto a la pendiente, ∂E/∂β₁, paso a paso | Documento |

**Evaluación del curso:** Tech Readings 10 % · Hands-on 70 % · Challenges 20 %.

## Hands-on 3 · Regresión lineal simple (Caso Benetton)

Implementa el modelo de regresión lineal simple construido en clase para estimar los coeficientes óptimos a partir del dataset del [Caso Benetton](https://www.displayr.com/what-is-linear-regression/), usando solo las columnas **Sales** (y) y **Advertising** (x).

$$
\beta_1 = \frac{n\sum xy - \sum x \sum y}{n\sum x^2 - \left(\sum x\right)^2}
\qquad
\beta_0 = \frac{\sum y - \beta_1 \sum x}{n}
\qquad
\hat{y} = \beta_0 + \beta_1 x
$$

- **Entrada:** ninguna. El dataset está declarado directamente en el código.
- **Salida:** la ecuación de regresión como texto, con β₀ y β₁ calculados por el programa, y las predicciones de Sales para cinco valores de Advertising que no están en el dataset.

```text
Ecuacion: y = [β0] + [β1]x

Predicciones de Sales:
  Advertising = [x1] -> [y1]
  ...
```

## Hands-on 4 · Tabla de frecuencia extendida

Agrupa en clases un dataset de números reales (30 o más datos, declarado en el código) e imprime la tabla con, en este orden:

1. Número de clases
2. Límites de clase
3. Frecuencia absoluta
4. Punto medio o marca de clase
5. Frecuencia relativa
6. Frecuencia absoluta acumulada
7. Frecuencia relativa acumulada
8. Porcentaje

## Cómo compilar y ejecutar

Requiere un compilador de C++ (por ejemplo, `g++`).

```bash
cd "Hands-on 3"
g++ main.cpp -o hands-on3
./hands-on3          # en Windows: .\hands-on3.exe
```

El mismo procedimiento aplica a `Hands-on 4`. Si el archivo fuente tiene otro nombre, ajusta el comando.

## Estructura del repositorio

```text
.
├── README.md
├── Tech Reading 1/
│   └── README.md
├── Hands-on 1/
│   └── README.md
├── Hands-on 2/
│   └── README.md
├── Hands-on 3/
│   └── main.cpp
├── Hands-on 4/
│   └── main.cpp
└── Challenge 1/
│   └── README.md
```

## Convenciones

- Una carpeta por assignment, con el nombre exacto del assignment.
- Solo código fuente: sin ejecutables ni archivos compilados.
- Los datos van declarados en el código; los programas no piden entradas.

## Avance

- [ ] Tech Reading 1
- [ ] Hands-on 1
- [ ] Hands-on 2
- [ ] Hands-on 3
- [ ] Hands-on 4
- [ ] Challenge 1

El código se sube después de su evaluación individual, según lo indicado por el docente.
>>>>>>> da4c2f452b73a0bc6531fd14fde363ccfecc3579
=======
# Probability-Stats
Actividades de Probabilidad y Estadística (2026B, TecMM Zapopan): regresión lineal simple en C++ con el Caso Benetton, tabla de frecuencia extendida, derivaciones de mínimos cuadrados y hojas de cálculo.
>>>>>>> 129536b2144d286d3770590c8e45b31af3d07ad4
