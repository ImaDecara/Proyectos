//
// Created by imano on 25/5/2023.
//

#include "cliente.h"




void cliente::obtenerCantidadClientes()
{
    string linea;
    ifstream clientesLectura(pathArchivoCliente, ios::in);

    if (clientesLectura.is_open()) {
        cantidadClientes = 0;
        //Cuenta la cantidad de lineas del archivo transacciones para obtener la cantidad de menuGestionTransacciones
        while (std::getline(clientesLectura, linea)) {
            cantidadClientes++;
        }

        clientesLectura.close();
    }
    else
    {
        throw std::logic_error("El archivo de clientes no pudo ser abierto");
    }
}

void cliente::cargarVectorLectura()
{
    obtenerCantidadClientes();

    ifstream clienteLectura(pathArchivoCliente,ios::in);
    if(clienteLectura.is_open())
    {
        for (int i = 0; i < cantidadClientes; ++i)
        {
            clienteLectura >> vectorClientes[i].numero_cliente >> vectorClientes[i].nombre_cliente >> vectorClientes[i].apellido_cliente >> vectorClientes[i].categoria_cliente >> vectorClientes[i].añio_cliente >> vectorClientes[i].estado_cliente;
        }
        clienteLectura.close();
    }
    else
    {
        throw std::logic_error("El archivo de clientes no pudo ser abierto");
    }
}

bool cliente::controlDatosAlta()
{
    bool resultado = false;
    if(numero_cliente > 0)
    {
        if(existe(numero_cliente) == false)
        {
            categoria_cliente = soporte.pasarMayusculas(categoria_cliente);

            if(categoria_cliente != "BLACK" && categoria_cliente != "ORO" && categoria_cliente != "PLATA" )
            {
                throw std::logic_error("La categoria ingresada es incorrecta");
            }
            if (controlCategoria(añio_cliente, categoria_cliente) == true)
            {
                resultado = true;
            }
        }
        else
        {
            throw std::logic_error("El numero de cliente ya existe en la base de datos !");
        }
    }
    else
    {
        throw std::logic_error("El numero de cliente debe ser mayor a cero");
    }

    return resultado;
}

bool cliente::controlDatosModificacionEstado()
{
    bool resultado = false;
    if(numero_cliente > 0)
    {
        if(existe(numero_cliente) == true)
        {
            resultado = true;
        }
        else
        {
            throw std::logic_error("El numero de cliente es inexistente");
        }

        return resultado;
    }
    else
    {
        throw std::logic_error("El numero de cliente debe ser mayor a cero");
    }
}

bool cliente::modificarEstado(string estadoAc)
{
    if(controlDatosModificacionEstado() == true)
    {
        string auxLineaCliente = "";

        ifstream archivoCliente(pathArchivoCliente,ios::app);
        ofstream archivoAuxiliar2(pathArchivoAuxiliarCliente, ios::out);

        if(archivoCliente.is_open() && archivoAuxiliar2.is_open())
        {
            for (int i = 0; i < cantidadClientes; ++i)
            {
                if(numero_cliente == vectorClientes[i].numero_cliente)
                {
                    vectorClientes[i].estado_cliente = estadoAc;
                }
                auxLineaCliente = to_string(vectorClientes[i].numero_cliente) + " " + vectorClientes[i].nombre_cliente + " " + vectorClientes[i].apellido_cliente + " " + vectorClientes[i].categoria_cliente + " " + to_string(vectorClientes[i].añio_cliente) + " " + vectorClientes[i].estado_cliente;
                archivoAuxiliar2 << auxLineaCliente << endl;
            }
            archivoCliente.close();
            archivoAuxiliar2.close();
        }
        else
        {
            throw std::logic_error("El archivo de clientes no pudo ser abierto");
        }

        remove(pathArchivoCliente);
        rename(pathArchivoAuxiliarCliente, pathArchivoCliente);
        return true;
    }

    return false;
}

bool cliente::controlCategoria(int anio, string categoria)
{
    int anioActual;

    //Obtenemos el los datos actuales
    anioActual = soporte.obtenerAnioActual();

    if(anio>anioActual)
    {
        throw std::logic_error("El año ingresado no puede ser mayor al actual");
        return false;
    }

    if(((anioActual - anio)<3)&&(categoria == "BLACK"))
    {
        throw std::logic_error("El cliente no puede ser 'BLACK', posee menos de 3 años de antiguedad. ");
        return false;
    }
    return true;
}

bool cliente::existe(int numero){
    cargarVectorLectura();

    if(numero > 0)
    {
        for (int i = 0; i < cantidadClientes; ++i)
        {
            int a = vectorClientes[i].numero_cliente;
            if(numero == vectorClientes[i].numero_cliente)
            {
                return true;
                break;
            }
        }
    }
    return false;
}

bool cliente::alta()
{
    string estado = "Activo";

    if(controlDatosAlta() == true)
    {
        ofstream archivoClienteEscritura(pathArchivoCliente, ios::app);

        if (archivoClienteEscritura.is_open())
        {
            //Asiganosmos el cliente
            archivoClienteEscritura << endl << numero_cliente << " " << nombre_cliente << " "
                                    << apellido_cliente << " "
                                    << categoria_cliente << " " << añio_cliente << " " << estado;

            archivoClienteEscritura.close();
            return true;
        }
        else
        {
            throw std::logic_error("El archivo de clientes no pudo ser abierto");
        }
    }

    return false;
}

bool cliente::activar()
{
    bool resultado = false;
    resultado =  modificarEstado("Activo");
    return resultado;
}

bool cliente::darDeBaja()
{
    bool resultado = false;
    resultado =   modificarEstado("Baja");
    return resultado;
}

bool cliente::buscar(){
    if (existe(numero_cliente) == true)
    {
        for (int i = 0; i < cantidadClientes; ++i)
        {
            if(numero_cliente == vectorClientes[i].numero_cliente)
            {
                numero_cliente = vectorClientes[i].numero_cliente;
                apellido_cliente = vectorClientes[i].apellido_cliente;
                nombre_cliente = vectorClientes[i].nombre_cliente;
                categoria_cliente= vectorClientes[i].categoria_cliente;
                estado_cliente = vectorClientes[i].estado_cliente;
                añio_cliente = vectorClientes[i].añio_cliente;
                return true;
            }
        }
    }
    return false;
}

bool cliente::esActivo(){
    if(numero_cliente > 0)
    {
        if(estado_cliente == "Activo")
        {
            return true;
        }
    }
    return false;
}
