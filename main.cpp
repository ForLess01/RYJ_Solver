#include <iostream>
#include <iomanip> // espaciado para la impresion de la tabla final combinada
using namespace std;

int min(int a, int b)
{
    if (a > b)
        return b;
    else
        return a;
}

int main()
{   
    
    cout << "Bienvenido : H3urisTius Suit Solver" << endl;
    cout << "------------------------------------" << endl;
    int opcion;
    do {
        cout << "\nSeleccione un metodo:\n"
            << " 1) Metodo 1\n"
            << " 2) Metodo 2\n"
            << " 3) Metodo 3\n"
            << " 0) Salir\n"
            << "Opcion: ";
        cin >> opcion;

        if (opcion == 0) {
            cout << "Saliendo..." << endl;
            return 0;
        }

        if (opcion < 0 || opcion > 3) {
            cout << "Opcion invalida, intente de nuevo.\n";
        }

    } while (opcion < 1 || opcion > 3);

    cout << "Introduzca numero de filas: ";
    int filas;
    cin >> filas;
    cout << "Introduzca numero de columnas: ";
    int columnas;
    cin >> columnas;

    cout << "El numero de filas y columnas debe ser mayor que cero." << endl;
    cout << "------------------------------------------------------" << endl;

    if (filas > 0 && columnas > 0)
    {
        cout << "Tamano de la tabla valido" << endl;
    }
    else
    {
        cout << "El numero de filas y columnas debe ser mayor que cero." << endl;
        return 1;
    }

    int tablaCost [filas][columnas];
    int tablaVal [filas+1][columnas+1];
    for (int i = 0; i < filas+1; i++)
        for (int j = 0; j < columnas+1; j++)
            tablaVal[i][j] = 0;

    cout << "Introduzca los costos para cada celda de la tabla(fila a fila):" << endl;
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            cin >> tablaCost[i][j];

    cout << "Introduzca los valores de la columna de Oferta:" << endl;
    for (int i = 0; i < filas; i++)
    {
        cin >> tablaVal[i][columnas];
    }
    cout << "Introduzca los valores de la fila de Demanda:" << endl;
    for (int j = 0; j < columnas; j++)
        cin >> tablaVal[filas][j];


    // Verificacion de Balanceo => OfertaTotal = DemandaTotal
    int OfertaTotal = 0, DemandaTotal = 0;

    for (int i = 0; i < filas; i++)
    {
        OfertaTotal += tablaVal[i][columnas];
    }
    for (int j = 0; j < columnas; j++)
    {
        DemandaTotal += tablaVal[filas][j];
    }

    if (OfertaTotal != DemandaTotal)
    {
        cout << "Error : Tabla no Balanceada";
        return 0;
    }

    int tabla[filas*2+2][columnas*2+2];
    int total = 0;
    // Eleccion del metodo
    switch (opcion) {
        case 1:
            {
                int oferta_temp[filas];
                for(int i=0; i<filas; ++i) oferta_temp[i] = tablaVal[i][columnas];

                int demanda_temp[columnas];
                for(int j=0; j<columnas; ++j) demanda_temp[j] = tablaVal[filas][j];

                bool primerIteracion = true;
                bool soloFilas = true;

                while (true) {
                    int sumaOferta = 0, sumaDemanda = 0;
                    for (int i = 0; i < filas; ++i) sumaOferta += oferta_temp[i];
                    for (int j = 0; j < columnas; ++j) sumaDemanda += demanda_temp[j];
                    if (sumaOferta == 0 || sumaDemanda == 0) break;

                    int rangosFilas[filas];
                    for(int i=0; i<filas; ++i) rangosFilas[i] = 0;

                    int rangosColumnas[columnas];
                    for(int j=0; j<columnas; ++j) rangosColumnas[j] = 0;
                    
                    for (int i = 0; i < filas; ++i) {
                        int minimoFila = 999999, maximoFila = -1;
                        if (oferta_temp[i] > 0) {
                            for (int j = 0; j < columnas; ++j) {
                                if (demanda_temp[j] > 0) {
                                    if(tablaCost[i][j] < minimoFila) minimoFila = tablaCost[i][j];
                                    if(tablaCost[i][j] > maximoFila) maximoFila = tablaCost[i][j];
                                }
                            }
                            if(maximoFila != -1) rangosFilas[i] = maximoFila - minimoFila;
                        }
                    }
                    for (int j = 0; j < columnas; ++j) {
                        int minimoColumna = 999999, maximoColumna = -1;
                        if(demanda_temp[j] > 0) {
                            for (int i = 0; i < filas; ++i) {
                                if (oferta_temp[i] > 0) {
                                    if(tablaCost[i][j] < minimoColumna) minimoColumna = tablaCost[i][j];
                                    if(tablaCost[i][j] > maximoColumna) maximoColumna = tablaCost[i][j];
                                }
                            }
                            if(maximoColumna != -1) rangosColumnas[j] = maximoColumna - minimoColumna;
                        }
                    }

                    int maxRangoFila = -1, indiceMaxRangoFila = -1;
                    int maxRangoColumna = -1, indiceMaxRangoColumna = -1;

                    if (primerIteracion) {
                        for (int i = 0; i < filas; ++i)
                            if (oferta_temp[i] > 0 && rangosFilas[i] > maxRangoFila) {
                                maxRangoFila = rangosFilas[i];
                                indiceMaxRangoFila = i;
                            }
                        for (int j = 0; j < columnas; ++j)
                            if (demanda_temp[j] > 0 && rangosColumnas[j] > maxRangoColumna) {
                                maxRangoColumna = rangosColumnas[j];
                                indiceMaxRangoColumna = j;
                            }
                        soloFilas = (maxRangoFila >= maxRangoColumna);
                        primerIteracion = false;
                    } else {
                        if (soloFilas) {
                            for (int i = 0; i < filas; ++i)
                                if (oferta_temp[i] > 0 && rangosFilas[i] > maxRangoFila) {
                                    maxRangoFila = rangosFilas[i];
                                    indiceMaxRangoFila = i;
                                }
                        } else {
                            for (int j = 0; j < columnas; ++j)
                                if (demanda_temp[j] > 0 && rangosColumnas[j] > maxRangoColumna) {
                                    maxRangoColumna = rangosColumnas[j];
                                    indiceMaxRangoColumna = j;
                                }
                        }
                    }

                    bool esFila = soloFilas;
                    int indice = esFila ? indiceMaxRangoFila : indiceMaxRangoColumna;

                    if (indice == -1) {
                        int r = -1, c = -1;
                         for(int i=0; i<filas; ++i){
                            if(oferta_temp[i] > 0) { r = i; break; }
                         }
                         for(int j=0; j<columnas; ++j){
                            if(demanda_temp[j] > 0) { c = j; break; }
                         }
                         if (r != -1 && c != -1) {
                             int cantidad = min(oferta_temp[r], demanda_temp[c]);
                             tablaVal[r][c] += cantidad;
                             oferta_temp[r] -= cantidad;
                             demanda_temp[c] -= cantidad;
                         } else {
                            break;
                         }
                         continue;
                    }


                    int menorCosto = 999999, indiceMenor = -1;
                    if (esFila) {
                        for (int j = 0; j < columnas; ++j)
                            if (demanda_temp[j] > 0 && tablaCost[indice][j] < menorCosto) {
                                menorCosto = tablaCost[indice][j];
                                indiceMenor = j;
                            }
                    } else {
                        for (int i = 0; i < filas; ++i)
                            if (oferta_temp[i] > 0 && tablaCost[i][indice] < menorCosto) {
                                menorCosto = tablaCost[i][indice];
                                indiceMenor = i;
                            }
                    }

                    if(indiceMenor == -1) {
                        primerIteracion = true;
                        continue;
                    };

                    int valorAsignado;
                    if (esFila) {
                        valorAsignado = min(oferta_temp[indice], demanda_temp[indiceMenor]);
                        tablaVal[indice][indiceMenor] += valorAsignado;
                        oferta_temp[indice] -= valorAsignado;
                        demanda_temp[indiceMenor] -= valorAsignado;
                    } else {
                        valorAsignado = min(oferta_temp[indiceMenor], demanda_temp[indice]);
                        tablaVal[indiceMenor][indice] += valorAsignado;
                        oferta_temp[indiceMenor] -= valorAsignado;
                        demanda_temp[indice] -= valorAsignado;
                    }
                }
            }
            break;
        case 2:
            while (true) {
                int fila_min = -1, min_oferta = 99999;
                for (int i = 0; i < filas; i++) {
                    if (tablaVal[i][columnas] > 0 && tablaVal[i][columnas] < min_oferta) {
                        min_oferta = tablaVal[i][columnas];
                        fila_min = i;
                    }
                }
                if (fila_min == -1) break;

                int col_min = -1, min_costo = 99999;
                for (int j = 0; j < columnas; j++) {
                    if (tablaVal[filas][j] > 0 && tablaCost[fila_min][j] < min_costo) {
                        min_costo = tablaCost[fila_min][j];
                        col_min = j;
                    }
                }

                if (col_min == -1) break;

                int cantidad = min(tablaVal[fila_min][columnas], tablaVal[filas][col_min]);
                tablaVal[fila_min][col_min] = cantidad;

                if (tablaVal[fila_min][columnas] == tablaVal[filas][col_min]) {
                    int segundo_col_min = -1, segundo_costo = 99999;
                    for (int j = 0; j < columnas; j++) {
                        if (j != col_min && tablaVal[filas][j] > 0 && tablaCost[fila_min][j] < segundo_costo) {
                            segundo_costo = tablaCost[fila_min][j];
                            segundo_col_min = j;
                        }
                    }

                    if (segundo_col_min != -1) {
                        tablaVal[fila_min][segundo_col_min] = 0;
                    }
                }

                tablaVal[fila_min][columnas] -= cantidad;
                tablaVal[filas][col_min] -= cantidad;
            }

            break;
        case 3:
            {
                int remSupply[filas];
                int remDemand[columnas];
                bool basicVars[filas][columnas];

                for (int i = 0; i < filas; i++) {
                    remSupply[i] = tablaVal[i][columnas];
                    for (int j = 0; j < columnas; j++) {
                        basicVars[i][j] = false;
                    }
                }
                for (int j = 0; j < columnas; j++) {
                    remDemand[j] = tablaVal[filas][j];
                }

                // --- Fase 1: Asignación Inicial por Filas ---
                for (int i = 0; i < filas; i++) {
                    if (remSupply[i] == 0) continue;
                    int minCostInRow = 999999;
                    for (int j = 0; j < columnas; j++) {
                        if (tablaCost[i][j] < minCostInRow) {
                            minCostInRow = tablaCost[i][j];
                        }
                    }
                    for (int j = 0; j < columnas; j++) {
                        if (tablaCost[i][j] == minCostInRow) {
                            if (remSupply[i] == 0) break;
                            int amount = min(remSupply[i], remDemand[j]);
                            tablaVal[i][j] += amount;
                            basicVars[i][j] = true;
                            remSupply[i] -= amount;
                            remDemand[j] -= amount;
                        }
                    }
                }

                // --- Fase 2: Completitud por Columnas ---
                struct Candidate { int cost; int index; };

                for (int j = 0; j < columnas; j++) {
                    int iterGuard = 0;
                    while (remDemand[j] > 0 && iterGuard < filas + 1) {
                        iterGuard++;
                        Candidate candidates[filas];
                        for (int i = 0; i < filas; i++) {
                            candidates[i].cost = tablaCost[i][j];
                            candidates[i].index = i;
                        }
                        for(int k=0; k<filas-1; k++) {
                            for(int l=0; l<filas-k-1; l++) {
                                if (candidates[l].cost > candidates[l+1].cost ||
                                (candidates[l].cost == candidates[l+1].cost && candidates[l].index > candidates[l+1].index)) {
                                    Candidate temp = candidates[l];
                                    candidates[l] = candidates[l+1];
                                    candidates[l+1] = temp;
                                }
                            }
                        }
                        bool allocatedInThisIteration = false;
                        for (int k = 0; k < filas; k++) {
                            int i_cand = candidates[k].index;
                            if (remSupply[i_cand] > 0 && !basicVars[i_cand][j]) {
                                int amount = min(remSupply[i_cand], remDemand[j]);
                                tablaVal[i_cand][j] += amount;
                                basicVars[i_cand][j] = true;
                                remSupply[i_cand] -= amount;
                                remDemand[j] -= amount;
                                allocatedInThisIteration = true;
                                break;
                            }
                        }
                        if (!allocatedInThisIteration) break;
                    }
                }
            }
            break;
        case 0:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opción inválida." << endl;
    }

    // Calculo de Z

    int ValorMax = 0;

    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            if (tablaVal[i][j] != 0)
            {
                ValorMax += tablaVal[i][j] * tablaCost[i][j];
            }
        }
    }
    // Uniendo Tablas en Tabla
    for (int i = 0; i < filas * 2 + 2; i++)
    {
        for (int j = 0; j < columnas * 2 + 2; j++)
        {
            if (i % 2 == 0 && j % 2 == 0 && (i / 2) < filas && (j / 2) < columnas)
                tabla[i][j] = tablaCost[i / 2][j / 2];
            else if (i % 2 != 0 && j % 2 != 0 && (i / 2) <= filas && (j / 2) <= columnas)
                tabla[i][j] = tablaVal[i / 2][j / 2];
            else
                tabla[i][j] = -1;
        }
    }

    // Impresion de tabla
    cout << "Imprimiendo Tabla:" << endl;
    for (int i = 0; i < filas * 2 + 2; i++)
    {
        for (int j = 0; j < columnas * 2 + 2; j++)
        {
            if (j == columnas * 2)
            {
                cout << " | ";
            }

            if (tabla[i][j] != -1)
            {
                cout << setw(4) << tabla[i][j];
            }
            else
            {
                cout << setw(4) << " ";
            }
        }

        if (i == filas * 2 - 1)
        {
            cout << endl;
            for (int j = 0; j < columnas * 2 + 2; j++)
            {
                if (j == columnas * 2)
                    cout << " | ";
                cout << "----";
            }
        }

        cout << endl;
    }

    cout << endl
         << "Costo total (Sol. Basica - Unica): " << ValorMax << endl;

    return 0;
}
