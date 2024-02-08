//
// Created by imano on 25/5/2023.
//

#include "transaccion.h"

void transaccion::cargarCantidadTransacciones() {
    string linea;
    ifstream transaccionLectura(pathArchivoTransaccion, ios::in);

    if (transaccionLectura.is_open())
    {
        cantidadTransacciones = 0;
        //Cuenta la cantidad de lineas del archivo transacciones para obtener la cantidad de menuGestionTransacciones
        while (std::getline(transaccionLectura, linea))
        {

            cantidadTransacciones++;
        }
        transaccionLectura.close();
    }
    else
    {
        throw std::logic_error("El archivo de clientes no pudo ser abierto");
    }

}

void transaccion::cargarVectorLectura(){

    cargarCantidadTransacciones();

    ifstream transaccionLectura(pathArchivoTransaccion,ios::in);

    if (transaccionLectura.is_open())
    {
        for (int i = 0; i <cantidadTransacciones; ++i)
        {
            transaccionLectura >> vectorTransacciones[i].numero_transaccion >> vectorTransacciones[i].cantidad_transaccion >> vectorTransacciones[i].tipo_transaccion >> vectorTransacciones[i].dia_transaccion >> vectorTransacciones[i].mes_transaccion >> vectorTransacciones[i].anio_transaccion >> vectorTransacciones[i].nro_cliente;
        }

        transaccionLectura.close();
    }

    else
    {
        throw std::logic_error("El archivo de transacciones no pudo ser abierto");
    }
}

int transaccion::obtenerSaldoCliente(int numero){
    int saldo = 0;
    cargarVectorLectura();

    for (int i = 0; i < cantidadTransacciones; ++i)
    {
        if(numero == vectorTransacciones[i].nro_cliente)
        {
            if(vectorTransacciones[i].tipo_transaccion == 'D')
            {
                saldo = saldo + vectorTransacciones[i].cantidad_transaccion;
            }

            if(vectorTransacciones[i].tipo_transaccion == 'E')
            {
                saldo = saldo - vectorTransacciones[i].cantidad_transaccion;
            }
        }
    }
    return saldo;
}

bool transaccion::nuevaTransaccion(cliente cli, int monto, char tipoTransaccion){
    try{
        ofstream archivoTransacciones(pathArchivoTransaccion,ios::app);

        int dia, mes, anio;
        string strMonto;

        if(cli.buscar() == true)
        {
            if(cli.esActivo()== false)
            {
                throw std::logic_error("Cliente dado de baja, no es posible realizar la operacion");
                return false;
            }

            if(monto > 0)
            {
                //Obtenemos el los datos actuales
                dia = soporte.obtenerDiaActual();
                mes = soporte.obtenerMesActual();
                anio = soporte.obtenerAnioActual();

                if (archivoTransacciones.is_open())
                {
                    cantidad_transaccion = monto;

                    //Asigna los valores por defecto
                    numero_transaccion = cantidadTransacciones + 1;
                    tipo_transaccion = tipoTransaccion;
                    dia_transaccion = dia;
                    mes_transaccion = mes;
                    anio_transaccion = anio;
                    nro_cliente = cli.GetAtributosCliente(cli.numero_cliente);

                    archivoTransacciones <<endl<< numero_transaccion << " " << cantidad_transaccion << " " << tipo_transaccion << " "
                                         << dia_transaccion << " " << mes_transaccion << " " << anio_transaccion << " "
                                         << nro_cliente;


                    archivoTransacciones.close();

                    //actualizamos cantidad de transacciones
                    cargarVectorLectura();

                    return true;

                }
                else
                {
                    throw std::logic_error("El archivo de transacciones no pudo ser abierto");
                    return false;
                }
            }
            else
            {
                throw std::logic_error("El monto debe ser mayor a cero");
                return false;
            }
        }
        else
        {
            throw std::logic_error("Cliente Inexistente!");
            return false;
        }

    }
    catch (std::logic_error string_caught)
    {
        throw std::logic_error(string_caught.what());
    }
}

bool transaccion::deposito(cliente cli, int monto){
    try
    {
        return nuevaTransaccion(cli,monto, 'D');
    }
    catch (std::logic_error string_caught)
    {
        throw std::logic_error(string_caught.what());
    }
}

bool transaccion::extraccion(cliente cli, int monto){
    try{
        int saldoActual = obtenerSaldoCliente(cli.numero_cliente);

        if(monto > saldoActual){
            throw std::logic_error( "Monto solicitado a extraer es mayor al saldo actual: $ " + to_string(saldoActual));
            return false;
        }

        return nuevaTransaccion(cli,monto, 'E');
    }
    catch (std::logic_error string_caught)
    {
        throw std::logic_error(string_caught.what());
    }
}
