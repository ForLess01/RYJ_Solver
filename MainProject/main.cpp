#define UNICODE
#define _UNICODE
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include "resource.h"
#include "rendoAlgorithm.h"

using namespace std;

HINSTANCE hInst;
int currentScreen = SCREEN_MAIN;

// Función para convertir de WCHAR a string
string WideStringToString(const WCHAR *wideString)
{
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wideString, -1, NULL, 0, NULL, NULL);
    string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wideString, -1, &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

// Función para convertir de string a WCHAR
wstring StringToWideString(const string &str)
{
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstrTo[0], size_needed);
    return wstrTo;
}

// Función para validar y obtener los datos de entrada
bool GetInputData(HWND hwndDlg, int &filas, int &columnas,
                  vector<vector<int>> &tablaCost,
                  vector<int> &oferta, vector<int> &demanda)
{
    // Obtener número de filas y columnas
    filas = GetDlgItemInt(hwndDlg, IDC_ROWS, NULL, FALSE);
    columnas = GetDlgItemInt(hwndDlg, IDC_COLUMNS, NULL, FALSE);

    if (filas <= 0 || columnas <= 0)
    {
        MessageBox(hwndDlg, L"El numero de filas y columnas debe ser mayor que cero", L"Error", MB_ICONERROR | MB_OK);
        return false;
    }

    // Obtener los datos de costos
    WCHAR costText[5000];
    GetDlgItemText(hwndDlg, IDC_EDIT_COSTS, costText, 5000);
    string costStr = WideStringToString(costText);
    istringstream costStream(costStr);

    tablaCost.resize(filas, vector<int>(columnas));
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            if (!(costStream >> tablaCost[i][j]))
            {
                MessageBox(hwndDlg, L"Error en los datos de costos. Asegúrese de ingresar todos los valores.", L"Error", MB_ICONERROR | MB_OK);
                return false;
            }
        }
    }

    // Obtener los datos de oferta
    WCHAR supplyText[1000];
    GetDlgItemText(hwndDlg, IDC_EDIT_SUPPLY, supplyText, 1000);
    string supplyStr = WideStringToString(supplyText);
    istringstream supplyStream(supplyStr);

    oferta.resize(filas);
    for (int i = 0; i < filas; i++)
    {
        if (!(supplyStream >> oferta[i]))
        {
            MessageBox(hwndDlg, L"Error en los datos de oferta. Asegúrese de ingresar todos los valores.", L"Error", MB_ICONERROR | MB_OK);
            return false;
        }
    }

    // Obtener los datos de demanda
    WCHAR demandText[1000];
    GetDlgItemText(hwndDlg, IDC_EDIT_DEMAND, demandText, 1000);
    string demandStr = WideStringToString(demandText);
    istringstream demandStream(demandStr);

    demanda.resize(columnas);
    for (int j = 0; j < columnas; j++)
    {
        if (!(demandStream >> demanda[j]))
        {
            MessageBox(hwndDlg, L"Error en los datos de demanda. Asegúrese de ingresar todos los valores.", L"Error", MB_ICONERROR | MB_OK);
            return false;
        }
    }

    return true;
}

// Función para resolver el método del Noroeste
void SolveNorthwest(HWND hwndDlg)
{
    int filas, columnas;
    vector<vector<int>> tablaCost;
    vector<int> oferta, demanda;

    if (!GetInputData(hwndDlg, filas, columnas, tablaCost, oferta, demanda))
        return;

    // Resolver el problema utilizando el método del Noroeste
    string result = solveNorthwestMethod(filas, columnas, tablaCost, oferta, demanda);

    // Mostrar el resultado en el cuadro de texto de resultados
    wstring wResult = StringToWideString(result);
    SetDlgItemText(hwndDlg, IDC_EDIT_RESULT, wResult.c_str());
}

// Función para el método de Yimmy (placeholder)
void SolveYimmy(HWND hwndDlg)
{
    int filas, columnas;
    vector<vector<int>> tablaCost;
    vector<int> oferta, demanda;

    if (!GetInputData(hwndDlg, filas, columnas, tablaCost, oferta, demanda))
        return;

    // Aquí iría la implementación del método de Yimmy
    // Por ahora mostramos un mensaje indicando que es un placeholder
    string result = "Método de Yimmy (Implementación pendiente)\n\n";
    result += "Filas: " + to_string(filas) + "\n";
    result += "Columnas: " + to_string(columnas) + "\n";
    result += "¡Este método será implementado próximamente!";

    wstring wResult = StringToWideString(result);
    SetDlgItemText(hwndDlg, IDC_EDIT_RESULT, wResult.c_str());
}

// Función para el método de Brayan (placeholder)
void SolveBrayan(HWND hwndDlg)
{
    int filas, columnas;
    vector<vector<int>> tablaCost;
    vector<int> oferta, demanda;

    if (!GetInputData(hwndDlg, filas, columnas, tablaCost, oferta, demanda))
        return;

    // Aquí iría la implementación del método de Brayan
    // Por ahora mostramos un mensaje indicando que es un placeholder
    string result = "Método de Brayan (Implementación pendiente)\n\n";
    result += "Filas: " + to_string(filas) + "\n";
    result += "Columnas: " + to_string(columnas) + "\n";
    result += "¡Este método será implementado próximamente!";

    wstring wResult = StringToWideString(result);
    SetDlgItemText(hwndDlg, IDC_EDIT_RESULT, wResult.c_str());
}

// Función para mostrar u ocultar controles según la pantalla actual
void SetScreenVisibility(HWND hwndDlg, int screen)
{
    // Ocultar todos los controles primero
    ShowWindow(GetDlgItem(hwndDlg, IDC_TITLE_MAIN), SW_HIDE);
    ShowWindow(GetDlgItem(hwndDlg, IDC_SUBTITLE_MAIN), SW_HIDE);
    ShowWindow(GetDlgItem(hwndDlg, IDC_BTN_START), SW_HIDE);

    ShowWindow(GetDlgItem(hwndDlg, IDC_STATIC_ROWS), SW_HIDE);
    ShowWindow(GetDlgItem(hwndDlg, IDC_ROWS), SW_HIDE);
    ShowWindow(GetDlgItem(hwndDlg, IDC_STATIC_COLUMNS), SW_HIDE);
    ShowWindow(GetDlgItem(hwndDlg, IDC_COLUMNS), SW_HIDE);
    ShowWindow(GetDlgItem(hwndDlg, IDC_BTN_NEXT), SW_HIDE);

    ShowWindow(GetDlgItem(hwndDlg, IDC_STATIC_COSTS), SW_HIDE);
    ShowWindow(GetDlgItem(hwndDlg, IDC_EDIT_COSTS), SW_HIDE);
    ShowWindow(GetDlgItem(hwndDlg, IDC_STATIC_SUPPLY), SW_HIDE);
    ShowWindow(GetDlgItem(hwndDlg, IDC_EDIT_SUPPLY), SW_HIDE);
    ShowWindow(GetDlgItem(hwndDlg, IDC_STATIC_DEMAND), SW_HIDE);
    ShowWindow(GetDlgItem(hwndDlg, IDC_EDIT_DEMAND), SW_HIDE);
    ShowWindow(GetDlgItem(hwndDlg, IDC_BTN_NORTHWEST), SW_HIDE);
    ShowWindow(GetDlgItem(hwndDlg, IDC_BTN_YIMMY), SW_HIDE);
    ShowWindow(GetDlgItem(hwndDlg, IDC_BTN_BRAYAN), SW_HIDE);
    ShowWindow(GetDlgItem(hwndDlg, IDC_BTN_BACK), SW_HIDE);
    ShowWindow(GetDlgItem(hwndDlg, IDC_STATIC_RESULT), SW_HIDE);
    ShowWindow(GetDlgItem(hwndDlg, IDC_EDIT_RESULT), SW_HIDE);

    // Mostrar solo los controles de la pantalla actual
    switch (screen)
    {
    case SCREEN_MAIN:
        ShowWindow(GetDlgItem(hwndDlg, IDC_TITLE_MAIN), SW_SHOW);
        ShowWindow(GetDlgItem(hwndDlg, IDC_SUBTITLE_MAIN), SW_SHOW);
        ShowWindow(GetDlgItem(hwndDlg, IDC_BTN_START), SW_SHOW);
        break;

    case SCREEN_INPUT_SIZE:
        ShowWindow(GetDlgItem(hwndDlg, IDC_STATIC_ROWS), SW_SHOW);
        ShowWindow(GetDlgItem(hwndDlg, IDC_ROWS), SW_SHOW);
        ShowWindow(GetDlgItem(hwndDlg, IDC_STATIC_COLUMNS), SW_SHOW);
        ShowWindow(GetDlgItem(hwndDlg, IDC_COLUMNS), SW_SHOW);
        ShowWindow(GetDlgItem(hwndDlg, IDC_BTN_NEXT), SW_SHOW);
        break;

    case SCREEN_INPUT_DATA:
        ShowWindow(GetDlgItem(hwndDlg, IDC_STATIC_COSTS), SW_SHOW);
        ShowWindow(GetDlgItem(hwndDlg, IDC_EDIT_COSTS), SW_SHOW);
        ShowWindow(GetDlgItem(hwndDlg, IDC_STATIC_SUPPLY), SW_SHOW);
        ShowWindow(GetDlgItem(hwndDlg, IDC_EDIT_SUPPLY), SW_SHOW);
        ShowWindow(GetDlgItem(hwndDlg, IDC_STATIC_DEMAND), SW_SHOW);
        ShowWindow(GetDlgItem(hwndDlg, IDC_EDIT_DEMAND), SW_SHOW);
        ShowWindow(GetDlgItem(hwndDlg, IDC_BTN_NORTHWEST), SW_SHOW);
        ShowWindow(GetDlgItem(hwndDlg, IDC_BTN_YIMMY), SW_SHOW);
        ShowWindow(GetDlgItem(hwndDlg, IDC_BTN_BRAYAN), SW_SHOW);
        ShowWindow(GetDlgItem(hwndDlg, IDC_BTN_BACK), SW_SHOW);
        ShowWindow(GetDlgItem(hwndDlg, IDC_STATIC_RESULT), SW_SHOW);
        ShowWindow(GetDlgItem(hwndDlg, IDC_EDIT_RESULT), SW_SHOW);
        break;
    }

    currentScreen = screen;
}

// Función para preparar la pantalla de datos
void PrepareDataScreen(HWND hwndDlg)
{
    int filas = GetDlgItemInt(hwndDlg, IDC_ROWS, NULL, FALSE);
    int columnas = GetDlgItemInt(hwndDlg, IDC_COLUMNS, NULL, FALSE);

    if (filas <= 0 || columnas <= 0)
    {
        MessageBox(hwndDlg, L"El numero de filas y columnas debe ser mayor que cero", L"Error", MB_ICONERROR | MB_OK);
        return;
    }

    // Generar valores por defecto para los controles de la pantalla 3
    wstring defaultCosts;
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            defaultCosts += L"0 ";
        }
        if (i < filas - 1)
        {
            defaultCosts += L"\r\n";
        }
    }

    wstring defaultSupply;
    for (int i = 0; i < filas; i++)
    {
        defaultSupply += L"0 ";
    }

    wstring defaultDemand;
    for (int j = 0; j < columnas; j++)
    {
        defaultDemand += L"0 ";
    }

    // Establecer los valores por defecto en los controles
    SetDlgItemText(hwndDlg, IDC_EDIT_COSTS, defaultCosts.c_str());
    SetDlgItemText(hwndDlg, IDC_EDIT_SUPPLY, defaultSupply.c_str());
    SetDlgItemText(hwndDlg, IDC_EDIT_DEMAND, defaultDemand.c_str());

    // Limpiar el área de resultados
    SetDlgItemText(hwndDlg, IDC_EDIT_RESULT, L"");

    // Cambiar a la pantalla de datos
    SetScreenVisibility(hwndDlg, SCREEN_INPUT_DATA);
}

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        // Valores predeterminados para la segunda pantalla
        SetDlgItemInt(hwndDlg, IDC_ROWS, 3, FALSE);
        SetDlgItemInt(hwndDlg, IDC_COLUMNS, 3, FALSE);

        // Mostrar la pantalla inicial
        SetScreenVisibility(hwndDlg, SCREEN_MAIN);
    }
        return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
        return TRUE;

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        // Botones de la pantalla inicial
        case IDC_BTN_START:
            SetScreenVisibility(hwndDlg, SCREEN_INPUT_SIZE);
            break;

        // Botones de la pantalla de dimensiones
        case IDC_BTN_NEXT:
            PrepareDataScreen(hwndDlg);
            break;

        // Botones de la pantalla de datos
        case IDC_BTN_NORTHWEST:
            SolveNorthwest(hwndDlg);
            break;

        case IDC_BTN_YIMMY:
            SolveYimmy(hwndDlg);
            break;

        case IDC_BTN_BRAYAN:
            SolveBrayan(hwndDlg);
            break;

        case IDC_BTN_BACK:
            SetScreenVisibility(hwndDlg, SCREEN_INPUT_SIZE);
            break;
        }
    }
        return TRUE;
    }
    return FALSE;
}

// For MinGW, we need to use WinMain even with UNICODE defined
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst = hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}