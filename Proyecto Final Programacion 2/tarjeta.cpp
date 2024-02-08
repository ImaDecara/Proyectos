//
// Created by imano on 3/6/2023.
//

#include "tarjeta.h"

void tarjeta::cargarCantidadCompras() {
    string linea;
    ifstream tarjetaLectura(pathArchivoTarjetas, ios::in);

    if (tarjetaLectura.is_open())
    {
        cantidadComprasTarjeta = 0;
        //Cuenta la cantidad de lineas del archivo transacciones para obtener la cantidad de compras
        while (std::getline(tarjetaLectura, linea))
        {
            cantidadComprasTarjeta++;
        }
        tarjetaLectura.close();
    }
    else
    {
        throw std::logic_error("El archivo de tarjetas no pudo ser abierto");
    }

}

void tarjeta::cargarVectorLectura(){

    cargarCantidadCompras();

    ifstream tarjetaLectura(pathArchivoTarjetas,ios::in);

    if (tarjetaLectura.is_open())
    {
        for (int i = 0; i <cantidadComprasTarjeta; ++i)
        {
            tarjetaLectura >> vectorTarjetas[i].numero_compra >>vectorTarjetas[i].numero_cliente >> vectorTarjetas[i].anio_Compra >> vectorTarjetas[i].mes_Compra >> vectorTarjetas[i].monto_compra;
        }

        tarjetaLectura.close();
    }
    else
    {
        throw std::logic_error("El archivo de tarjeta no pudo ser abierto");
    }
}

int tarjeta::comprasClienteMes(cliente cli, int mes, int anio){
    cargarVectorLectura();

    int montoMensual = 0;

    for (int i = 0; i < cantidadComprasTarjeta; ++i)
    {
        if((cli.numero_cliente == vectorTarjetas[i].numero_cliente) && mes == vectorTarjetas[i].mes_Compra && anio == vectorTarjetas[i].anio_Compra)
        {
            montoMensual = montoMensual + vectorTarjetas[i].monto_compra;
        }
    }
    return montoMensual;
}

int tarjeta::comprasCliente(cliente cli){
    cargarVectorLectura();

    int monto = 0;

    for (int i = 0; i < cantidadComprasTarjeta; ++i)
    {
        if((cli.numero_cliente == vectorTarjetas[i].numero_cliente))
        {
            monto = monto + vectorTarjetas[i].monto_compra;
        }
    }
    return monto;
}

bool tarjeta::nuevaCompra(cliente cli, int monto)
{
    try{
        ofstream archivoTarjeta(pathArchivoTarjetas, ios::app);

        int  montoMensual = 0, montoControl = 0, mes, anio;
        bool resultado = false;

        //Fecha
        mes = soporte.obtenerMesActual();
        anio = soporte.obtenerAnioActual();


        if(cli.buscar() == true)
        {

            if(cli.esActivo()== false)
            {
                throw std::logic_error("Cliente dado de baja, no es posible realizar la operacion");
            }

            montoMensual = comprasClienteMes(cli, mes, anio);

            if (soporte.pasarMayusculas(cli.GetAtributosCliente(cli.categoria_cliente)) == "PLATA") {
                montoControl = 50000;
            }
            if (soporte.pasarMayusculas(cli.GetAtributosCliente(cli.categoria_cliente)) == "ORO") {
                montoControl = 75000;
            }
            if (soporte.pasarMayusculas(cli.GetAtributosCliente(cli.categoria_cliente)) == "BLACK") {
                montoControl = 250000;
            }

            //Si el monto de la compra + el monto acumulado mensual es menor al monto al monto que permitido por su categoria, permite efectuar la compra
            if ((monto + montoMensual) < montoControl)
            {

                if (archivoTarjeta.is_open())
                {
                    numero_compra = cantidadComprasTarjeta + 1;
                    numero_cliente = cli.numero_cliente;
                    anio_Compra = anio;
                    mes_Compra = mes;
                    monto_compra = monto;

                    archivoTarjeta << endl << numero_compra << " " << numero_cliente << " " << anio_Compra << " "
                                   << mes_Compra << " " << monto_compra;

                    archivoTarjeta.close();
                    cargarVectorLectura();

                    resultado = true;
                }
                else
                {
                    throw std::logic_error("El archivo de tarjeta no pudo ser abierto");
                }
            }
            else
            {
                throw std::logic_error("No se puede registrar la compra de $ " + to_string(monto) + ".\n" +
                                       "El monto maximo mensual de compra de su categoria " + "'" + cli.GetAtributosCliente(cli.categoria_cliente) + "' es de $ " +  to_string((montoControl)) + ".\n" +
                                       "Monto de compras acumulado mensual: $ " + to_string(montoMensual)+ ".\n" +
                                       "Saldo disponible para compras mensual: $ " + to_string(montoControl - montoMensual));
            }
        }
        else
        {
            throw std::logic_error("Cliente Inexistente!");
        }

        return resultado;

    }
    catch (std::logic_error string_caught) {
        throw std::logic_error(string_caught.what());
    }
}
