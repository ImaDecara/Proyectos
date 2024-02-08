#include <iostream>
#include <iomanip>
#include <string>
#include "tarjeta.h"
#include "transaccion.h"

using namespace std;

// variables globales del sistema
cliente cl;
transaccion tx;
tarjeta tarj;
general soporte;

//Inicialización de atributos estaticos
int cliente::cantidadClientes = 0;
cliente cliente::vectorClientes[500];

int transaccion::cantidadTransacciones = 0;
transaccion transaccion::vectorTransacciones[500];

int tarjeta::cantidadComprasTarjeta = 0;
tarjeta tarjeta::vectorTarjetas[500];

// Funciones Generales
    void enterParaContinuar(){
        cout<<endl;
        system("pause");
        cout<<endl;
    }
    void limpiarPantalla()
    {
       int filas = 50;
        do {
            cout<<endl;
            filas -= 1;
        } while (filas !=0);
    }


//Funciones Mensajes
    void mostrarMensajeError(string mensajeError)
    {
        const char* charMensaje = mensajeError.c_str();

        printf(" \n");
        printf(" \n");
        printf("-- E R R O R --------------------------------------------------------------\n");
        printf(charMensaje);
        printf(" \n");
        printf("--------------------------------------------------------------------------\n");
        printf(" \n");
        printf(" \n");
        enterParaContinuar();
    }
    void mostrarMensajeAtencion(string mensajeAtencion)
    {
        const char* charMensaje = mensajeAtencion.c_str();
        printf(" \n");
        printf(" \n");
        printf("-- A T E N C I O N --------------------------------------------------------\n");
        printf(charMensaje);
        printf(" \n");
        printf("--------------------------------------------------------------------------\n");
        printf(" \n");
        printf(" \n");
        enterParaContinuar();
    }
    void mostrarMensajeConfirmacion(string mensajeConfirmacion)
    {
        const char* charMensaje = mensajeConfirmacion.c_str();
        printf(" \n");
        printf(" \n");
        printf("-- T I E M P O - F I N A L -----------------------------------------------\n");
        printf(charMensaje);
        printf("--------------------------------------------------------------------------\n");
        printf(" \n");
        printf(" \n");
        enterParaContinuar();
    }


//Funciones Cuadros
    void cuadroCliente(){
        cout<<"Numero "<<std::setw(15)<<" Nombre   "<<std::setw(15)<<"  Apellido  "<<std::setw(15)<<"  Tipo   "<<std::setw(15)<<"  A#o   "<<std::setw(15)<<"  Estado   "<<std::setw(15)<<"  Dinero Cuenta"<<endl;
        cout <<"-----------------------------------------------------------------------------------------------"<<endl;
    }
    void cuadroTransacciones(){
        cout<<"Numero "<<std::setw(15)<<" Cantidad   "<<std::setw(15)<<"  Tipo  "<<std::setw(15)<<"  Dia   "<<std::setw(15)<<"  Mes   "<<std::setw(15)<<"  A#o   "<<std::setw(15)<<"  Numero Cliente"<<endl;
        cout <<"-----------------------------------------------------------------------------------------------"<<endl;
    }
    void cuadroTarjetaCompra(){
        cout<<"Numero "<<std::setw(15)<<std::setw(15)<<"  Mes   "<<std::setw(15)<<"  A#o   "<<std::setw(15)<<"  Monto"<<endl;
        cout <<"-----------------------------------------------------------------------------------------------"<<endl;
    }


//Transacciones
    void transaccionesMostrar(){
        limpiarPantalla();
        cout << "" << endl;
        cout << "--> LISTADO TRANSACCIONES<--" << endl;
        cout << "" << endl;

        tx.cargarVectorLectura();
        cuadroTransacciones();

        for (int i = 0; i < transaccion::cantidadTransacciones; ++i)
        {

            std::cout << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].numero_transaccion)
                      << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].cantidad_transaccion)
                      << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].tipo_transaccion)
                      << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].dia_transaccion)
                      << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].mes_transaccion)
                      << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].anio_transaccion)
                      << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].nro_cliente) << std::endl;
        }
        enterParaContinuar();
    }
    void transaccionSemeste(int anio, int semestre){
        limpiarPantalla();
        cout << "" << endl;
        cout << "--> LISTADO SEMESTRALES <--" << endl;
        cout << "" << endl;

        tx.cargarVectorLectura();
        cuadroTransacciones();

        bool existeTransaccion = false;
        int mesDesde, mesHasta;

        if(semestre == 1){
            mesDesde = 1;
            mesHasta = 6;
        }
        else
        {
            mesDesde = 7;
            mesHasta = 12;
        }
        for (int i = 0; i < transaccion::cantidadTransacciones; ++i)
        {

            if(anio == transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].anio_transaccion) && transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].mes_transaccion) >=mesDesde && transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].mes_transaccion) <=mesHasta)
            {

                std::cout << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].numero_transaccion)
                          << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].cantidad_transaccion)
                          << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].tipo_transaccion)
                          << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].dia_transaccion)
                          << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].mes_transaccion)
                          << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].anio_transaccion)
                          << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].nro_cliente) << std::endl;

                existeTransaccion = true;

            }
        }

        if(existeTransaccion == false){
            mostrarMensajeAtencion("No hay transacciones segun lo solicitado");
            return;
        }
        enterParaContinuar();

}
    void transaccionesSemestral(){

        try{
            limpiarPantalla();
            int op=0, anio=0;
            string strAnio;

            cout << "--> TRANSACCIONES SEMESTRALES <--" << endl;
            cout << "" << endl;
            cout << "Ingrese el a#o: ";
            cin>>strAnio;

            anio = soporte.EsUnNumero(strAnio);

            if(anio <= 0)
            {
                throw std::logic_error("El valor ingresado debe ser numerico o mayor a cero");
                return;
            }

            cout << "" << endl;
            cout << "" << endl;
            cout << "Seleccione el Semestre: " << endl;
            cout << "" << endl;
            cout << "1. Primer Semestre" << endl;
            cout << "2. Segundo Semestre" << endl;
            cout << "3. Regresar el Menu" << endl;
            cout << "" << endl;
            cout << "Opcion: ";
            cin >> op;

            switch (op) {
                case 1:
                    transaccionSemeste(anio, 1);
                    break;

                case 2:
                    transaccionSemeste(anio, 2);
                    break;

                case 3:
                    return;
                    break;
            }
        }
        catch (std::logic_error string_caught) {
            mostrarMensajeError(string_caught.what());
        }
    }
    void transaccionesAnio(){
        try{
            limpiarPantalla();
            int anio = 0;
            string strAnio;

            cout << "" << endl;
            cout << "--> LISTADO TRANSACCIONES POR A#O<--" << endl;
            cout << "" << endl;

            tx.cargarVectorLectura();

            cout<<"Ingrese el a#o: ";
            cin>>strAnio;

            anio = soporte.EsUnNumero(strAnio);

            if(anio <= 0)
            {
                throw std::logic_error("El valor ingresado debe ser numerico o mayor a cero");
                return;
            }

            cuadroTransacciones();

            for (int i = 0; i < transaccion::cantidadTransacciones; ++i) {

                if(anio == transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].anio_transaccion)){

                    std::cout << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].numero_transaccion)
                              << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].cantidad_transaccion)
                              << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].tipo_transaccion)
                              << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].dia_transaccion)
                              << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].mes_transaccion)
                              << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].anio_transaccion)
                              << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].nro_cliente) << std::endl;
                }

            }
            enterParaContinuar();
        }
        catch (std::logic_error string_caught) {
            mostrarMensajeError(string_caught.what());
        }
    }


//Clientes
    void clienteAlta()
    {
        try
        {
            limpiarPantalla();

            //---Inicio---
            cout << "" << endl;
            cout << "-->  NUEVO CLIENTE <--" << endl;
            cout << "" << endl;

            string strNumero, strAnio;
            int numero=0, anio=0, anioActual, diferenciaAnio;
            string nombre, apellido, tipo;

            anioActual = soporte.obtenerAnioActual();

            cout << "" << endl;
            cout << "-->  DATOS DEL CLIENTE <--" << endl;
            cout << "" << endl;
            cout << "" << endl;
            cout << "Numero: ";
            cin>>strNumero;

            numero = soporte.EsUnNumero(strNumero);

            if (numero > 0)
            {
                cl.SetAtributosCliente(cl.numero_cliente,numero);
            }
            else
            {
                throw std::logic_error("El valor ingresado debe ser numerico o mayor a cero");
            }

            cout << "Nombre: ";
            cin>>nombre;
            cl.SetAtributosCliente(cl.nombre_cliente,nombre);

            cout << "Apellido: ";
            cin>>apellido;
            cl.SetAtributosCliente(cl.apellido_cliente,apellido);

            cout << "A#o: ";
            cin>>strAnio;
            anio = soporte.EsUnNumero(strAnio);

            if (anio <= anioActual)
            {
                cl.SetAtributosCliente(cl.añio_cliente,anio);
            }
            else
            {
                throw std::logic_error("El a#o ingresado debe ser numerico y menor a#o actual");
            }

            cout << "Categoria (black, oro, plata): ";
            cin>>tipo;

            cl.SetAtributosCliente(cl.categoria_cliente,tipo);

            bool resultado = false;
            resultado = cl.alta();

            if (resultado == true)
            {
                mostrarMensajeConfirmacion("Cliente dado de Alta Correctamente");
            }
            else
            {
                mostrarMensajeError("Ocurrio un error al dar de Alta el Cliente");
            }
        }
        catch (std::logic_error string_caught)
        {
            mostrarMensajeError(string_caught.what());
        }
    }
    int clientePedirNumero()
    {
       try{
           int numero =0;
           string strNumero;

           cout << "Ingrese el numero del cliente: ";
           cin >> strNumero;

           numero = soporte.EsUnNumero(strNumero);

           if (numero > 0)
           {
               return numero;
           }
           else
           {
               throw std::logic_error("El valor ingresado debe ser numerico o mayor a cero");
           }
       }
       catch (std::logic_error string_caught)
       {
           mostrarMensajeError(string_caught.what());
           return 0;
       }
}
    void clienteModificarEstado(){
        bool resultado = false;
        int op;
        do{
            limpiarPantalla();
            cout << ""<< endl;
            cout << "--> MODIFICAR ESTADO DE LA CUENTA <--"<< endl;
            cout << ""<< endl;

            cout<<"Ingrese el nuevo estado de la cuenta: ";
            cout << ""<< endl;
            cout << "Nuevo estado de Cuenta"<< endl;
            cout << ""<< endl;
            cout << "1. Activo"<< endl;
            cout << "2. Baja"<< endl;
            cout << "3. Salir"<< endl;
            cout << ""<< endl;
            cout<<"Opcion: ";
            cin>>op;


            switch (op) {
                case 1:
                    resultado = cl.activar();
                    op=3;
                    break;

                case 2:
                    resultado = cl.darDeBaja();
                    op=3;
                    break;

                case 3:
                    return;
                    break;
            }

            }while(op!=3);

            if(resultado == true)
            {
                mostrarMensajeConfirmacion("Estado Correctamente Actualizado");
            }
            else
            {
                mostrarMensajeConfirmacion("No se pudo modificar el estado");
            }
    }
    void mostrarClientes(){
        limpiarPantalla();
        cout << "" << endl;
        cout << "--> CLIENTES <--" << endl;
        cout << "" << endl;

        cl.cargarVectorLectura();

        cuadroCliente();

        for (int i = 0; i < cliente::cantidadClientes; ++i) {
            std::cout << std::left << std::setw(15) << cliente::vectorClientes[i].GetAtributosCliente(cliente::vectorClientes[i].numero_cliente)
                      << std::left << std::setw(15) << cliente::vectorClientes[i].GetAtributosCliente(cliente::vectorClientes[i].nombre_cliente)
                      << std::left << std::setw(15) << cliente::vectorClientes[i].GetAtributosCliente(cliente::vectorClientes[i].apellido_cliente)
                      << std::left << std::setw(15) << cliente::vectorClientes[i].GetAtributosCliente(cliente::vectorClientes[i].categoria_cliente)
                      << std::left << std::setw(15) << cliente::vectorClientes[i].GetAtributosCliente(cliente::vectorClientes[i].añio_cliente)
                      << std::left << std::setw(15) << cliente::vectorClientes[i].GetAtributosCliente(cliente::vectorClientes[i].estado_cliente)
                      << std::left << std::setw(15) << tx.obtenerSaldoCliente(cliente::vectorClientes[i].numero_cliente) << std::endl;
        }

        enterParaContinuar();
    }
    void mostrarDatosCliente()
    {
        cout << endl;
        cout << " - Cliente: " << cl.GetAtributosCliente(cl.apellido_cliente) <<" "<<cl.GetAtributosCliente(cl.nombre_cliente) << endl;
        cout << " - Cuenta: " << cl.GetAtributosCliente(cl.numero_cliente)  << endl;
        cout << " - Categoria: " << cl.GetAtributosCliente(cl.categoria_cliente)   << endl;
        cout << " - Estado: " << cl.GetAtributosCliente(cl.estado_cliente)  << endl;
        cout << " - Saldo Actual: $"<< tx.obtenerSaldoCliente(cl.GetAtributosCliente(cl.numero_cliente))<< endl;
        cout << " - Compras Tarjeta Mes Actual: $"<<tarj.comprasClienteMes(cl, soporte.obtenerMesActual(), soporte.obtenerAnioActual())<< endl;
        cout << ""<< endl;
    }
    void clientePorNumero() {
        limpiarPantalla();
        int numero = 0;
        bool exiteCliente = false;
        cout << "" << endl;
        cout << "--> BUSCAR CLIENTE POR NUMERO <--" << endl;
        cout << "" << endl;

        numero = clientePedirNumero();

        if(numero > 0)
        {
            cl.numero_cliente = numero;

            if(cl.buscar() == true)
            {
                cl.cargarVectorLectura();

                cuadroCliente();

                for (int i = 0; i < cliente::cantidadClientes; ++i)
                {
                    if(numero == cliente::vectorClientes[i].GetAtributosCliente(cliente::vectorClientes[i].numero_cliente))
                    {
                        std::cout << std::left << std::setw(15) << cliente::vectorClientes[i].GetAtributosCliente(cliente::vectorClientes[i].numero_cliente)
                                  << std::left << std::setw(15) << cliente::vectorClientes[i].GetAtributosCliente(cliente::vectorClientes[i].nombre_cliente)
                                  << std::left << std::setw(15) << cliente::vectorClientes[i].GetAtributosCliente(cliente::vectorClientes[i].apellido_cliente)
                                  << std::left << std::setw(15) << cliente::vectorClientes[i].GetAtributosCliente(cliente::vectorClientes[i].categoria_cliente)
                                  << std::left << std::setw(15) << cliente::vectorClientes[i].GetAtributosCliente(cliente::vectorClientes[i].añio_cliente)
                                  << std::left << std::setw(15) << cliente::vectorClientes[i].GetAtributosCliente(cliente::vectorClientes[i].estado_cliente)
                                  << std::left << std::setw(15) << tx.obtenerSaldoCliente(cliente::vectorClientes[i].numero_cliente) << std::endl;
                        break;
                    }
                }

                enterParaContinuar();

            }
            else
            {
                mostrarMensajeAtencion("Cliente inexitente");
                return;
            }
        }

    }
    void transaccionesPorCliente(){

        limpiarPantalla();
        int numero = 0;
        bool existeTransaccion = false;


        cout << "" << endl;
        cout << "--> TRANSACCIONES POR CLIENTE<--" << endl;
        cout << "" << endl;

        numero = clientePedirNumero();

        if(numero > 0)
        {
            cl.numero_cliente = numero;

            if(cl.buscar() == true)
            {
                mostrarDatosCliente();

                tx.cargarVectorLectura();

                cuadroTransacciones();

                for (int i = 0; i < transaccion::cantidadTransacciones; ++i)
                {
                    if(cl.numero_cliente == transaccion::vectorTransacciones[i].nro_cliente)
                    {

                        std::cout << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].numero_transaccion)
                                  << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].cantidad_transaccion)
                                  << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].tipo_transaccion)
                                  << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].dia_transaccion)
                                  << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].mes_transaccion)
                                  << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].anio_transaccion)
                                  << std::left << std::setw(15) << transaccion::vectorTransacciones[i].GetAtributosTransaccion(transaccion::vectorTransacciones[i].nro_cliente) << std::endl;

                        existeTransaccion = true;
                    }
                }

                if(existeTransaccion == true)
                {
                    cout<<endl;
                    cout<<"SALDO ACTUAL: $ "<<tx.obtenerSaldoCliente(cl.numero_cliente );
                    cout<<endl;
                }
                else
                {
                    mostrarMensajeAtencion("No hay transacciones segun lo solicitado");
                    return;
                }
                enterParaContinuar();
            }
            else
            {
                mostrarMensajeAtencion("Cliente ingresado inexistente !");
                return;
            }

        }
    }


//Transacciones Depositos - Extracciones
    void depositos(){
        try{
            int numero, monto = 0;
            string strMonto;
            bool resultado = false;

            //---Inicio---
            cout << "" << endl;
            cout << "--> DEPOSITO EN CUENTA CLIENTE <--" << endl;
            cout << "" << endl;

            numero = clientePedirNumero();

            if (numero <= 0)
            {
                return;
            }

            cl.numero_cliente = numero;

            if(cl.buscar() == true)
            {

                mostrarDatosCliente();

                cout << "" << endl;
                cout << "Ingrese el monto a depositar a la cuenta: $";
                cin >> strMonto;

                monto = soporte.EsUnNumero(strMonto);

                if(monto > 0)
                {
                    resultado = tx.deposito(cl,monto);

                    if (resultado == true)
                    {
                        mostrarMensajeConfirmacion("Deposito Correctamente Realizado .\n Saldo actual en su cuenta: " + to_string(tx.obtenerSaldoCliente(cl.numero_cliente )));
                    }
                    else
                    {
                        mostrarMensajeError("El archivo de transacciones no pudo ser abierto");
                    }
                }
                else
                {
                    mostrarMensajeAtencion("El valor ingresado debe ser numerico o mayor a cero");
                }
            }
            else
            {
                mostrarMensajeAtencion("Cliente Inexistente!");
            }

        }
        catch (std::logic_error string_caught) {
            mostrarMensajeError(string_caught.what());
        }
    }
    void extracciones()
    {
        try{
            int numero, monto = 0;
            string strMonto;
            bool resultado = false;

            //---Inicio---
            cout << "" << endl;
            cout << "--> EXTRACCION EN CUENTA CLIENTE <--" << endl;
            cout << "" << endl;

            numero = clientePedirNumero();

            if(numero <= 0){
                return;
            }

            cl.numero_cliente = numero;

            if(cl.buscar() == true)
            {
                mostrarDatosCliente();

                cout << "" << endl;
                cout << "Ingrese el monto a extraer a la cuenta: $";
                cin >> strMonto;

                monto = soporte.EsUnNumero(strMonto);

                if(monto > 0){

                    resultado = tx.extraccion(cl,monto);
                    if (resultado == true)
                    {
                        //cargamos las transacciones
                        tx.cargarVectorLectura();

                        mostrarMensajeConfirmacion("Extraccion Correctamente Realizada .\n Saldo actual en su cuenta: " + to_string(tx.obtenerSaldoCliente(cl.numero_cliente)));
                    }
                    else
                    {
                        mostrarMensajeError("El archivo de transacciones no pudo ser abierto");
                    }
                }
                else
                {
                    throw std::logic_error("El valor ingresado debe ser numerico o mayor a cero");
                }
            }
            else
            {
                mostrarMensajeAtencion("Cliente Inexistente!");
            }

        }
        catch (std::logic_error string_caught)
        {
            mostrarMensajeError(string_caught.what());
        }
    }


//Tarjetas Compras
    void tarjetaNuevaCompra()
    {
        try{
            limpiarPantalla();
            int numero = 0, monto = 0;
            bool resultado = false;
            string strMonto;

            //---Inicio---
            cout << "" << endl;
            cout << "--> COMPRA CON TARJETA <--" << endl;
            cout << "" << endl;

            numero = clientePedirNumero();

            if(numero <= 0){
                return;
            }

            cl.numero_cliente = numero;

            if(cl.buscar() == true)
            {
                mostrarDatosCliente();

                if(cl.esActivo() == false){
                    mostrarMensajeAtencion("Cliente dado de baja, no es posible realizar la operacion");
                    return;
                }

                cout << "" << endl;
                cout << "Ingrese el monto de la compra: $";
                cin >> strMonto;

                monto = soporte.EsUnNumero(strMonto);

                if(monto > 0)
                {
                    resultado = tarj.nuevaCompra(cl,monto);

                    if (resultado == true)
                    {
                        mostrarMensajeConfirmacion("Compra ingresada correctamente.");
                    }
                }
                else
                {
                    mostrarMensajeAtencion("El valor ingresado debe ser numerico o mayor a cero");
                }
            }
            else
            {
                mostrarMensajeAtencion("Cliente Inexistente!");
            }
        }
        catch (std::logic_error string_caught)
        {
            mostrarMensajeError(string_caught.what());
        }
    }
    void tarjetasCompraPorCliente()
    {
       limpiarPantalla();
        int numero = 0;
        bool existeCompra = false;


        cout << "" << endl;
        cout << "--> COMPRA CON TARJETA POR CLIENTE<--" << endl;
        cout << "" << endl;

        numero = clientePedirNumero();

        if(numero <= 0){
            return;
        }

        cl.numero_cliente = numero;

        if(cl.buscar() == true)
        {
            mostrarDatosCliente();

            tarj.cargarVectorLectura();

            cuadroTarjetaCompra();

            for (int i = 0; i < tarjeta::cantidadComprasTarjeta; ++i)
            {
                if(numero == tarjeta::vectorTarjetas[i].numero_cliente)
                {

                    std::cout << std::left << std::setw(15) << tarjeta::vectorTarjetas[i].GetAtributosTarjeta(tarjeta::vectorTarjetas[i].numero_compra)
                              << std::left << std::setw(15) << tarjeta::vectorTarjetas[i].GetAtributosTarjeta(tarjeta::vectorTarjetas[i].mes_Compra)
                              << std::left << std::setw(15) << tarjeta::vectorTarjetas[i].GetAtributosTarjeta(tarjeta::vectorTarjetas[i].anio_Compra)
                              << std::left << std::setw(15) << tarjeta::vectorTarjetas[i].GetAtributosTarjeta(tarjeta::vectorTarjetas[i].monto_compra)
                              << std::endl;

                    existeCompra = true;
                }
            }

            if(existeCompra == true)
            {
                cout<<endl;
                cout<<"COMPRAS TOTALES CON TARJETA: $ "<<tarj.comprasCliente(cl);
                cout<<endl;
            }
            else
            {
                mostrarMensajeAtencion("No hay compras con tarjeta para mostrar segun lo solicitado");
                return;
            }
            enterParaContinuar();
        }
        else
        {
            mostrarMensajeAtencion("Cliente ingresado inexistente !");
            return;
        }
    }


//Menu
    void menuClienteEstado(){
        try{
            limpiarPantalla();

            int numero=0,op=0;
            string strNumero, strOp;

            bool exiteCliente = false;
            cout << ""<< endl;
            cout << "--> CLIENTES <--"<< endl;
            cout << ""<< endl;

            numero = clientePedirNumero();

            if(numero <= 0){
                return;
            }

            cl.numero_cliente = numero;

            if(cl.buscar() == true)
            {

                mostrarDatosCliente();
                exiteCliente = true;

                cout << ""<< endl;
                cout << ""<< endl;
                cout << "1. Actualizar Estado de cuenta"<< endl;
                cout << "2. Menu"<< endl;
                cout << ""<< endl;
                cout << "Opcion: ";
                cin >> strOp;

                op = soporte.EsUnNumero(strOp);

                if (op <= 0)
                {
                    mostrarMensajeError("El valor ingresado es invalido");
                    op = 0;
                }

                switch (op)
                {
                    case 1:
                        clienteModificarEstado();

                    case 2:
                        return;
                        break;
                }

            }
            else
            {
                mostrarMensajeAtencion("Cliente ingresado inexistente !");
                return;
            }

        }catch (std::logic_error string_caught) {

            mostrarMensajeError(string_caught.what());
        }

    }
    void menuGestionTransacciones()
    {
        int op = 0;
        string strOp;

        do {
            limpiarPantalla();
            cout << "" << endl;
            cout << "--> TRANSACCIONES <--" << endl;
            cout << "" << endl;
            cout << "1. Realizar Deposito" << endl;
            cout << "2. Realizar Extraccion" << endl;
            cout << "3. Transacciones por periodo de 6 meses" << endl;
            cout << "4. Transacciones por periodo de 1 a#o" << endl;
            cout << "5. Todas las transacciones" << endl;
            cout << "6. Nueva Compra con Tarjeta de Credito" << endl;
            cout << "7. Compras con Tarjeta de Credito" << endl;
            cout << "8. Regresar el Menu" << endl;
            cout << "" << endl;
            cout << "Opcion: ";
            cin >> strOp;

            op = soporte.EsUnNumero(strOp);

            if (op <= 0)
            {
                mostrarMensajeError("El valor ingresado es invalido");
                op = 0;
            }


            switch (op)
            {
                case 1:
                    depositos();
                    break;

                case 2:
                    extracciones();
                    break;

                case 3:
                    transaccionesSemestral();
                    break;

                case 4:
                    transaccionesAnio();
                    break;

                case 5:
                    transaccionesMostrar();
                    break;

                case 6:
                    tarjetaNuevaCompra();
                    break;

                case 7:
                    tarjetasCompraPorCliente();
                    break;

                case 8:
                    return;
                    break;

            }
        }while(op!=8);
    }
    void menuGestionClientes(){
        int op=0;
        string strOp;

        do {

            limpiarPantalla();
            cout << "" << endl;
            cout << "--> GESTION DE CLIENTES <--" << endl;
            cout << "" << endl;
            cout << "1. Ver / Modificar estado del cliente." << endl;
            cout << "2. Mostrar Listado de Clientes." << endl;
            cout << "3. Buscar Cliente por su Numero." << endl;
            cout << "4. Buscar Transaccion por Cliente" << endl;
            cout << "5. Alta Cliente" << endl;
            cout << "6. Menu" << endl;
            cout << "" << endl;
            cout << "Opcion: ";
            cin >> strOp;

            op = soporte.EsUnNumero(strOp);

            if (op <= 0)
            {
                mostrarMensajeError("El valor ingresado es invalido");
                op = 0;
            }

            cout << "" << endl;
            cout << "" << endl;

            switch (op)
            {
                case 1:
                    menuClienteEstado();
                    break;

                case 2:
                    mostrarClientes();
                    break;

                case 3:
                    clientePorNumero();
                    break;

                case 4:
                    transaccionesPorCliente();
                    break;

                case 5:
                    clienteAlta();
                    break;

                case 6:
                    return;
                    break;
            }
        }while(op!=6);
    }
    void menuPrincipal (){
            limpiarPantalla();
            cout << "--> MENU PRINCIPAL <--" << endl;
            cout << "" << endl;
            cout << "1. Gestion de Clientes." << endl;
            cout << "2. Gestion de Operaciones." << endl;
            cout << "3. Salir." << endl;
            cout << "" << endl;

            cout << "Opcion: ";
            return;
    }


int main() {

        limpiarPantalla();
        int op = 0;
        string strOp;

        //Inicio del Programa
        cout << "---> BIENVENIDO <---" << endl;

        //Menu
        do {
            limpiarPantalla();
            cout << " " << endl;
            menuPrincipal();
            cin >> strOp;

            op = soporte.EsUnNumero(strOp);

            if (op <= 0)
            {
                mostrarMensajeError("El valor ingresado es invalido");
                op = 0;
            }

            switch (op)
            {
                case 1:
                    menuGestionClientes();
                    break;

                case 2:
                    menuGestionTransacciones();
                    break;
            }
        } while (op != 3);
}




