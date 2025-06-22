# RYJ_Solver: H3urisTius

![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

## Descripción

**H3urisTius** es una herramienta de optimización implementada en C++ diseñada para resolver problemas de transporte en investigación de operaciones. El problema de transporte consiste en determinar la mejor manera de distribuir bienes desde múltiples orígenes a múltiples destinos, minimizando los costos totales de transporte.

## Características

- Implementación en C++ de múltiples algoritmos para resolver problemas de transporte:
  - Método de la esquina noroeste
  - Método de costo mínimo
  - Método de aproximación de Vogel (VAM)
  - Método stepping-stone para optimización
  - MODI (Modified Distribution Method)
- Interfaz robusta para definir y resolver problemas de transporte
- Visualización de soluciones y rutas óptimas
- Análisis de sensibilidad para evaluar cambios en los parámetros
- Soporte para problemas equilibrados y no equilibrados

## Instalación

```bash
# Clonar el repositorio
git clone https://github.com/ForLess01/RYJ_Solver.git

# Entrar al directorio
cd RYJ_Solver

# Compilar el proyecto (usando CMake)
mkdir build
cd build
cmake ..
make
```

## Uso

### Ejemplo básico

Para probar la lógica de asignación de transporte, puedes compilar y ejecutar el programa principal `rendoMethod.cpp`, que te solicitará datos de ejemplo (filas, columnas, costos, oferta y demanda), y luego mostrará la solución:

```cpp
#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    // Desde la línea de comandos, compila y ejecuta rendoMethod.cpp:
    //   g++ rendoMethod.cpp -o rendoMethod
    //   ./rendoMethod
    // Ingresa los valores que solicita el programa y obtendrás la solución en la consola.

    system("g++ rendoMethod.cpp -o rendoMethod");
    system("./rendoMethod");

    return 0;
}
```

### Visualización de soluciones

En esta versión, la visualización se realiza a través de la consola, imprimiendo una tabla con los valores de cada celda y el costo total al final.

## Fundamentos teóricos

El problema de transporte se formula matemáticamente como:

Minimizar:
  
$$Z = \sum_{i=1}^{m} \sum_{j=1}^{n} c_{ij} \, x_{ij}$$

Sujeto a:
  
$$\sum_{j=1}^{n} x_{ij} \leq a_i \quad \forall i = 1, 2, \dots, m$$

$$\sum_{i=1}^{m} x_{ij} \geq b_j \quad \forall j = 1, 2, \dots, n$$

$$x_{ij} \geq 0 \quad \forall i = 1, \dots, m;\; j = 1, \dots, n$$

Donde:
- $x_{ij}$ es la cantidad transportada desde el origen $i$ al destino $j$.
- $c_{ij}$ es el costo unitario de transporte desde el origen $i$ al destino $j$.
- $a_i$ es la oferta (capacidad) del origen $i$.
- $b_j$ es la demanda del destino $j$.

## Algoritmos implementados

### Método de la esquina noroeste

Proporciona una solución inicial factible, comenzando desde la esquina superior izquierda de la tabla de costos y asignando la máxima cantidad posible según las restricciones de oferta y demanda.

### Método de costo mínimo

Ofrece una solución inicial de mejor calidad, seleccionando las celdas con los costos unitarios más bajos y asignando la máxima cantidad posible.

### Método de aproximación de Vogel (VAM)

Calcula para cada fila y columna la diferencia entre los dos costos más bajos, eligiendo la mayor diferencia para realizar la asignación.

### Optimización mediante MODI y Stepping Stone

Permite mejorar una solución básica factible hasta alcanzar la solución óptima.

## Ejemplos y casos de uso

- Distribución de productos desde fábricas a almacenes
- Asignación de personal a diferentes proyectos
- Planificación de rutas para flotas de vehículos
- Optimización de cadenas de suministro

## Requisitos del sistema

- Compilador de C++ compatible con C++17 o superior
- CMake 3.10 o superior
- Bibliotecas gráficas (opcional, para visualización adicional)

## Documentación

Para una documentación completa de la API y ejemplos adicionales, consulta la documentación detallada.

## Contribuciones

Las contribuciones son bienvenidas. Por favor, siga estos pasos:

1. Haga fork del repositorio  
2. Cree una rama para su funcionalidad (`git checkout -b feature/amazing-feature`)  
3. Realice sus cambios y haga commit (`git commit -m 'Add some amazing feature'`)  
4. Suba los cambios a la rama (`git push origin feature/amazing-feature`)  
5. Abra un Pull Request  

## Licencia

Este proyecto está licenciado bajo la Licencia MIT - vea el archivo `LICENSE` para más detalles.

## Autores

- **ForLess01** - *Trabajo inicial* - [ForLess01](https://github.com/ForLess01)

## Agradecimientos

- Agradecemos a todos los investigadores y matemáticos que han contribuido al campo de la optimización de transporte
- Inspirado en los trabajos de F.L. Hitchcock y L.V. Kantorovich sobre problemas de transporte
