#include <iostream>
#include <fstream>
#include "general.h"

using namespace std;

#ifndef CLIENTE_H
#define CLIENTE_H

class cliente {

private:
    //Constantes Generales Archivos Cliente y Transacciones ORIGINALES!
    const char *pathArchivoCliente = "C:\\Users\\imano\\OneDrive\\Escritorio\\Prot\\Proyecto Final Programacion\\Clientes.txt";
    const char *pathArchivoAuxiliarCliente = "C:\\Users\\imano\\OneDrive\\Escritorio\\Prot\\Proyecto Final Programacion\\auxClientes.txt";

    general soporte;

public:
    //variables estaticas
    static int cantidadClientes;
    static cliente vectorClientes[500];//Con 500 posiciones disponibles a usar

    int numero_cliente, añio_cliente;
    string apellido_cliente, nombre_cliente, categoria_cliente, estado_cliente;



private:
    //Funciones o Metodos privadas
    bool controlCategoria(int , string );

    bool existe(int);

    void obtenerCantidadClientes();

    bool controlDatosAlta();

    bool controlDatosModificacionEstado();

    bool modificarEstado(string) ;


public:
    cliente()  {
        numero_cliente = 0;
        añio_cliente = 0;
        nombre_cliente = "";
        apellido_cliente = "";
        categoria_cliente = "";
        estado_cliente = "";
    }

    cliente(int numero_c, string nombre_c, string apellido_c, string categoria_c, int añio_c, int estado_c, int depo_total, int extra_total, int din_total ){
        numero_cliente = numero_c;
        añio_cliente = añio_c;
        nombre_cliente = nombre_c;
        apellido_cliente = apellido_c;
        categoria_cliente = categoria_c;
        estado_cliente = estado_c;
    }

    template<typename T>
    T GetAtributosCliente(const T& atributos) const {
        return atributos;
    }

    template <typename S>
    void SetAtributosCliente(S& atributo, const S& valor) {
        atributo = valor;
    }

    void cargarVectorLectura();

    bool alta();

    bool activar();

    bool darDeBaja();

    bool buscar();

    bool esActivo();
};
#endif // CLIENTE_H




