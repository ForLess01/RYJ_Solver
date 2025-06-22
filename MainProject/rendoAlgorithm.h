#ifndef NORTHWEST_ALGORITHM_H
#define NORTHWEST_ALGORITHM_H

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;
// Solución del problema de transporte utilizando el Método del Noroeste
string solveNorthwestMethod(int filas, int columnas,
                                 vector<vector<int>> &tablaCost,
                                 vector<int> &oferta,
                                 vector<int> &demanda);

// Función auxiliar
int min(int a, int b);

#endif // NORTHWEST_ALGORITHM_H
