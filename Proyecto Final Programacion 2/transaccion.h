#include <iostream>
#include <fstream>
#include "cliente.h"
#include "general.h"


using namespace std;

#ifndef TRANSACCION_H
#define TRANSACCION_H

class transaccion {

private:
    //Constantes Generales Archivos  Transacciones
    const char *pathArchivoTransaccion = "C:\\Users\\imano\\OneDrive\\Escritorio\\Prot\\Proyecto Final Programacion\\transacciones.txt";

    general soporte;

public:
    //variables estaticas
    static int cantidadTransacciones;
    static transaccion vectorTransacciones[500]; //Lo creamos con 500 posiciones disponibles a usar

    int numero_transaccion, cantidad_transaccion, dia_transaccion, mes_transaccion, anio_transaccion, nro_cliente;
    char tipo_transaccion;



private:
    void cargarCantidadTransacciones();

    bool nuevaTransaccion(cliente, int, char);

public:
    transaccion(int numero_cliente_, int numero_t, int cantidad_t, char tipo_t, int dia_t, int mes_t, int añio_t) {

        numero_transaccion = numero_t;
        cantidad_transaccion = cantidad_t;
        tipo_transaccion = tipo_t;
        dia_transaccion = dia_t;
        mes_transaccion = mes_t;
        anio_transaccion = añio_t;
        nro_cliente = numero_cliente_;
    }

    transaccion() {

        numero_transaccion = 0;
        cantidad_transaccion = 0;
        tipo_transaccion = 'N';
        dia_transaccion = 0;
        mes_transaccion = 0;
        anio_transaccion = 0;
        nro_cliente = 0;
    }

    template<typename T>
    T GetAtributosTransaccion(const T &atributos) const {
        return atributos;
    }

    template<typename S>
    void SetAtributosTransaccion(S &atributo, const S &valor) {
        atributo = valor;
    }

    void cargarVectorLectura();

    int obtenerSaldoCliente(int);

    bool deposito(cliente, int);

    bool extraccion(cliente, int);
};

#endif // TRANSACCION_H

