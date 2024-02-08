#include <istream>
#include <fstream>
#include "cliente.h"
#include "general.h"

using namespace std;

#ifndef TARJETA_H
#define TARJETA_H

class tarjeta {

private:
    //Constantes Generales Archivos
    const char *pathArchivoTarjetas = "C:\\Users\\imano\\OneDrive\\Escritorio\\Prot\\Proyecto Final Programacion\\tarjetas.txt";

    general soporte;

public:
    int numero_cliente, monto_compra, mes_Compra, anio_Compra, numero_compra;

    //variables estaticas
    static int cantidadComprasTarjeta;
    static tarjeta vectorTarjetas[500]; //Lo creamos con 500 posiciones disponibles a usar



private:
    void cargarCantidadCompras();

public:
    tarjeta(int numero_cliente_, int numero_compra_,int monto_, int mes_, int anio_){
        numero_cliente = numero_cliente_;
        monto_compra = monto_;
        mes_Compra = mes_;
        anio_Compra = anio_;
        numero_compra = numero_compra_;
     }

    tarjeta(){
        numero_cliente = 0;
        monto_compra = 0;
        mes_Compra = 0;
        anio_Compra = 0;
        numero_compra = 0;
    }

    template<typename T>
    T GetAtributosTarjeta(const T& atributos) const {
        return atributos;
    }

    template <typename S>
    void SetAtributosTarjeta(S& atributo, const S& valor) {
        atributo = valor;
    }

    void cargarVectorLectura();

    int comprasClienteMes(cliente, int, int );

    int comprasCliente(cliente);

    bool nuevaCompra(cliente, int);
};

#endif // TARJETA_H

