#include "rendoAlgorithm.h"

using namespace std;
// Función auxiliar que ya existía en northWest.cpp
int min(int a, int b)
{
    if (a > b)
        return b;
    else
        return a;
}

// Implementación del método del noroeste adaptado para la interfaz gráfica
string solveNorthwestMethod(int filas, int columnas,
                                 vector<vector<int>> &tablaCost,
                                 vector<int> &oferta,
                                 vector<int> &demanda)
{
    ostringstream result;

    // Crear tablaVal (equivalente a la estructura en northWest.cpp)
    vector<vector<int>> tablaVal(filas + 1, vector<int>(columnas + 1, 0));

    // Colocar oferta y demanda en tablaVal
    for (int i = 0; i < filas; i++)
        tablaVal[i][columnas] = oferta[i];

    for (int j = 0; j < columnas; j++)
        tablaVal[filas][j] = demanda[j];

    // Verificación de Balanceo => OfertaTotal = DemandaTotal
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
        result << "Error: Tabla no Balanceada\n";
        result << "Total Oferta: " << OfertaTotal << "\n";
        result << "Total Demanda: " << DemandaTotal << "\n";
        return result.str();
    }

    result << "Tabla Balanceada (Oferta = Demanda = " << OfertaTotal << ")\n\n";

    vector<vector<int>> tabla(filas * 2 + 2, vector<int>(columnas * 2 + 2));

    // Logica de deslizamiento y eliminación de filas o columnas.
    int mov = 0;
    for (int i = 0; i < filas; i++)
    {
        for (int j = mov; j < columnas; j++)
        {
            tablaVal[i][j] = min(tablaVal[filas][j], tablaVal[i][columnas]);
            tablaVal[i][columnas] -= tablaVal[i][j];
            tablaVal[filas][j] -= tablaVal[i][j];
            if (tablaVal[filas][j] == 0 && tablaVal[i][columnas] == 0)
            {
                mov++;
                break;
            }
            else
            {
                if (tablaVal[filas][j] == 0)
                {
                    mov++;
                    continue;
                }
                if (tablaVal[i][columnas] == 0)
                {
                    break;
                }
            }
        }
    }

    // Cálculo de Z (valor máximo)
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

    // Impresión de tabla en el resultado
    result << "Tabla de Asignación:\n";
    for (int i = 0; i < filas * 2 + 2; i++)
    {
        for (int j = 0; j < columnas * 2 + 2; j++)
        {
            if (j == columnas * 2)
            {
                result << " | ";
            }

            if (tabla[i][j] != -1)
            {
                result << setw(4) << tabla[i][j];
            }
            else
            {
                result << setw(4) << " ";
            }
        }

        if (i == filas * 2 - 1)
        {
            result << "\n";
            for (int j = 0; j < columnas * 2 + 2; j++)
            {
                if (j == columnas * 2)
                    result << " | ";
                result << "----";
            }
        }
        result << "\n";
    }

    result << "\nCosto total (Sol. Básica - Única): " << ValorMax;

    return result.str();
}
