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
        cout << "\nSeleccione un método:\n"
             << " 1) Método 1\n"
             << " 2) Método 2\n"
             << " 3) Método 3\n"
             << " 0) Salir\n"
             << "Opción: ";
        cin >> opcion;
    } while (opcion != 0);

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
    int tablaVal [filas+1][columnas+1] = {0}; // Inicializar la tabla de costos con ceros

    cout << "Introduzca los costos para cada celda de la tabla(fila * fila):" << endl;
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

    // Eleccion del metodo
    switch (opcion) {
        case 1:
            //ejecutarHeuristica1(filas, columnas, tablaCost, tablaVal);
            break;
        case 2:
            // ejecutarHeuristica2(filas, columnas, tablaCost, tablaVal);
            break;
        case 3:
            // ejecutarHeuristica3(filas, columnas, tablaCost, tablaVal);
            break;
        case 0:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opción inválida." << endl;
    }


    // Logica deslizamiento y eliminacion de filas o columnas.


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