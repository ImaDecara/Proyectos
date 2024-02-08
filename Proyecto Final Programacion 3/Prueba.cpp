#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <windows.h>
using namespace std;


void mostrarMensajeError(string mensajeError)
{
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );


    const char* charMensaje = mensajeError.c_str();

    SetConsoleTextAttribute(hConsole, 4);
    printf(" \n");
    printf("-- E R R O R --------------------------------------------------------------\n");
    printf(charMensaje);
    printf(" \n");
    printf("--------------------------------------------------------------------------\n");
    printf(" \n");
    SetConsoleTextAttribute(hConsole, 7);
}
void mostrarMensajeConfirmacionTiempo(string mensajeConfirmacion, double tiempo)
{
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

    const char* charMensaje = mensajeConfirmacion.c_str();

    SetConsoleTextAttribute(hConsole, 2);
    printf(" \n");
    printf("-- T I E M P O - F I N A L - E J E C U C I O N -----------------------------------------------\n");
    printf(charMensaje);
    cout<<tiempo;
    printf(" \n");
    printf("--------------------------------------------------------------------------\n");
    printf(" \n");
    printf(" \n");
    SetConsoleTextAttribute(hConsole, 7);
}
void mostrarMensajeInicioTiempo(string mensajeInicio)
{
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

    const char* charMensaje = mensajeInicio.c_str();

    SetConsoleTextAttribute(hConsole, 6);
    printf(" \n");
    printf(charMensaje);
    printf(" \n");
    SetConsoleTextAttribute(hConsole, 7);
}
void menuInicio() {
    cout << " --> MENU <-- \n" << endl;
    cout << "1. Total_art_dif" << endl;
    cout << "2. Total_art" << endl;
    cout << "3. Min_stock [n]" << endl;
    cout << "4. Min_stock [n],[deposito] " << endl;
    cout << "5. Stock [nombre_articulo] " << endl;
    cout << "6. Stock [nombre_articulo],[depósito]" << endl;
    cout << "7. Max_Stock [n] " << endl;
    cout << "8. Salir\n" << endl;
    cout << " Opcion -->  ";
}

void leerArchivoCSV(vector<vector<string>>& columna) {
    string linea;
    char c;
    string cad;
    setlocale(LC_CTYPE, "Spanish");
    ifstream archivo("Inventariado Fisico.csv");

    while (getline(archivo, linea)) {
        vector<string> row;
        linea = " " + linea + ",";
        int cont = 0;
        for (int x = 0; x < linea.length(); ++x) {
            char c = linea[x];
            if (c != ',') {
                cad += c;
            } else {
                if (cad.empty())
                    cad = "0";
                row.push_back(cad);
                cad = "";
            }
        }
        columna.push_back(row);
    }
}

int convertir(string dato) {
    int numero;
    stringstream convert(dato);
    convert >> numero;
    return numero;
}

void contar_articulos_por_deposito(vector<vector<string>>& columna) {

    clock_t begin;

    mostrarMensajeInicioTiempo("Comenzando a medir Tiempo");
    begin = clock();

    cout << "1. Total arcticulos diferentes\n" << endl;

    vector<int> depositos(5, 0);
    for (size_t i = 0; i < columna.size(); ++i) {
        // Ensure that the number of columns (7) is within bounds
        if (columna[i].size() == 8) {
            for (size_t dep = 3; dep <= 7; ++dep) {
                int num = !columna[i][dep].empty() ? convertir(columna[i][dep]) : 0;
                depositos[dep - 3] += num;
            }
        }
    }

    for (size_t dep = 0; dep < 5; ++dep) {
        cout << " - Deposito " << (dep + 1) << ": " << depositos[dep] << " articulos" << endl;
    }

    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "\n" << endl;
    mostrarMensajeConfirmacionTiempo("Tiempo final: ",elapsed_secs);
}

void totalArticulosDiferentes(vector<vector<string>>& columna) {

    clock_t begin;

    mostrarMensajeInicioTiempo("Comenzando a medir Tiempo");
    cout << "2. Total de articulos\n" << endl;

    begin = clock();


    int total_articulos = static_cast<int>(columna.size());
    cout << "Total de articulos encontrados: " << total_articulos <<"\n"<< endl;
    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    mostrarMensajeConfirmacionTiempo("Tiempo final: ",elapsed_secs);
}

void min_stock(vector<vector<string>>& columna, int n) {

    clock_t begin;

    mostrarMensajeInicioTiempo("Comenzando a medir Tiempo");

    begin = clock();

    cout << "  | Articulos |      -      | Stock |\n" << endl;

    for (size_t x = 0; x < columna.size(); ++x) {
        if (columna[x].size() == 8) {
            int num = 0;
            for (size_t j = 3; j <= 7; ++j) {
                num += convertir(columna[x][j]);
            }
            if (num <= n && num > 0) {
                cout << columna[x][2] << " ==> " << num << endl;
            }
        }
    }

    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    mostrarMensajeConfirmacionTiempo("Tiempo final: ",elapsed_secs);
}

void min_stock_con_depo(vector<vector<string>>& columna, int min, int dep) {

    clock_t begin;

    mostrarMensajeInicioTiempo("Comenzando a medir Tiempo");

    begin = clock();

    dep = 2 + dep;

    cout << " | Articulo |      -     | Articulos del Deposito | " << endl;

    for (size_t x = 0; x < columna.size(); ++x) {
        int num = convertir(columna[x][dep]);
        if (num <= min && num > 0) {
            cout << columna[x][2] << " ===> " << num << endl;
        }
    }

    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    mostrarMensajeConfirmacionTiempo("Tiempo final: ",elapsed_secs);

}

void stock_individual(vector<vector<string>>& columna, string nombre) {

    int i = 0;
    int suma = 0;

    clock_t begin;

    mostrarMensajeInicioTiempo("Comenzando a medir Tiempo");

    begin = clock();

    while (i < columna.size() && columna[i][2] != nombre) {
        i++;
    }

    if (i < columna.size()) {
        for (size_t j = 3; j < 8; j++) {
            int num = convertir(columna[i][j]);
            cout << "Deposito " << j - 2 << ": " << num << endl;
            suma += num;
        }
        cout << "Total : " << suma << "\n";
    } else {
        mostrarMensajeError("El elemento ingresado es inexistente !!\n");
    }

    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    mostrarMensajeConfirmacionTiempo("Tiempo final: ",elapsed_secs);
}

void stock_individual_dep(vector<vector<string>>& columna, string nombre, int dep) {

    int i = 0;

    clock_t begin;

    mostrarMensajeInicioTiempo("Comenzando a medir Tiempo");

    begin = clock();

    while (i < columna.size() && columna[i][2] != nombre) {
        i++;
    }

    if (i < columna.size()) {
        cout << "Cantidad: " << columna[i][dep + 2] << endl;
    } else {
        mostrarMensajeError("El numero de deposito ingresado es inexistente !!");
    }

    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    mostrarMensajeConfirmacionTiempo("Tiempo final: ",elapsed_secs);
}

void max_stock(vector<vector<string>>& columna, int n) {

    clock_t begin;

    mostrarMensajeInicioTiempo("Comenzando a medir Tiempo");

    begin = clock();

    cout << "  | Articulos |      -      | Stock |\n" << endl;

    for (size_t x = 0; x < columna.size(); ++x) {
        if (columna[x].size() == 8) {
            int num = 0;
            for (size_t j = 3; j <= 7; ++j) {
                num += convertir(columna[x][j]);
            }
            if (num >= n) {
                cout << columna[x][2] << " ==> " << num << endl;
            }
        }
    }
    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    mostrarMensajeConfirmacionTiempo("Tiempo final: ",elapsed_secs);
}



int main() {
    vector<vector<string>> columna;
    int opcion = 0, num = 0, dep = 0, tiempo=0;
    string art;

    leerArchivoCSV(columna);

    cout << "Bienvenidos !!\n" << endl;

    while (true) {
        menuInicio();
        cin >> opcion;

        switch (opcion) {
            case 1:
                contar_articulos_por_deposito(columna);
                break;

            case 2:
                totalArticulosDiferentes(columna);
                break;

            case 3:
                cout << "3. Minimo stock\n" << endl;
                cout << "Minimo de stock: ";
                cin >> num;
                min_stock(columna, num);
                break;

            case 4:
                cout << "4. Minimo stock del deposito seleccionado\n" << endl;
                cout << "Minimo de stock: ";
                cin >> num;
                cout << "Numero de deposito: ";
                cin >> dep;

                if (dep <= 4 && 0<dep){
                    min_stock_con_depo(columna, num, dep);
                }else{
                    mostrarMensajeError("No existe ese deposito");
                }
                break;

            case 5:
                cout << "5. Stock individual\n";
                cout << "Ingrese el nombre del articulo: ";
                cin.ignore();
                getline(cin, art);
                stock_individual(columna, art);
                break;

            case 6:
                cin.ignore();
                cout << "6. Stock individual por deposito\n";
                getline(cin, art);
                cout << "Ingrese el numero de deposito: ";
                cin >> dep;
                stock_individual_dep(columna, art, dep);
                break;

            case 7:
                cout << "7. Stock maximo\n";
                cout << "Maximo de stock: ";
                cin >> num;
                max_stock(columna, num);
                break;

            case 8:
                cout << "Gracias por usar nuestro programa." << endl;
                return 0;

            default:
                cout << "Opción no válida. Por favor, seleccione una opción válida." << endl;
                break;
        }
    }
}

