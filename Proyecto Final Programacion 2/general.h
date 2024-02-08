#include <string>
#include <ctime>
#include <stdexcept>


using namespace std;

#ifndef GENERAL_H
#define GENERAL_H

class general {

public:
    int obtenerDiaActual(){
        int dia = 0;

        time_t now = time(0);
        struct tm *localTime = localtime(&now);

        //Obtenemos el los datos actuales
        dia = localTime->tm_mday;

        return dia;
    }

    int obtenerMesActual(){
        int mes = 0;

        time_t now = time(0);
        struct tm *localTime = localtime(&now);

        //Obtenemos el los datos actuales
        mes = localTime->tm_mon + 1;

        return mes;
    }

    int obtenerAnioActual()
    {
        int anio = 0;

        time_t now = time(0);
        struct tm *localTime = localtime(&now);

        //Obtenemos el los datos actuales
        anio = localTime->tm_year + 1900;

        return anio;

    }

    string pasarMayusculas(const std::string& input)
    {
        std::string result = input;
        for (char& c : result)
        {
            c = std::toupper(c);
        }
        return result;
    }

    int EsUnNumero(string numeroString){
        try{
            int numero = std::stoi(numeroString);

            return numero;
        }
        catch (const std::invalid_argument& e)
        {
            return 0;
        }
    }
};

#endif // GENERAL_H

