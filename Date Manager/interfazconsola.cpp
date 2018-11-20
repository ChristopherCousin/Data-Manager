#include <iostream>
#include <string>
#include <fstream>
#include "interfazconsola.h"
#include "databaseconnector.h"

using namespace std;

void InterfazConsola::show()
{

    string respuesta;
    string nombre;
    string apellidos;
    string telefono;
    string busqueda;

    cout << "                       Bienvenido al gestor de datos." << endl;
    cout << "                       -----------------------------\n" << endl;
    do
    {
        cout << "\n                       ----------- Menu -----------\n" << endl;
        cout << "                       Anyadir datos.          (1)" << endl;
        cout << "                       Ver TODOS los datos.    (2)" << endl;
        cout << "                       Borrar TODOS los datos. (3)" << endl;
        cout << "                       Buscar.                 (4)" << endl;
        cout << "                       Salir.                  (5)" << endl;
        cin >> respuesta;

        if( respuesta == "1" )
        {
            cout << "                       ----------- Panel -----------\n" << endl;
            cout << "Nombre: " << endl;
            cin >> nombre;
            while ( nombre.length() > g_databasemanager.nombreLimit || nombre.length() < 3 )
            {
                cout << "El nombre que has introducido tiene " << nombre.length() << " caracteres" << endl;
                cout << "*Minimo 3 caracteres: " << endl;
                cout << "*Máximo 20 caracteres: " << endl;
                cout << "\nNombre: " << endl;
                cin >> nombre;
            } /// END WHILE

            cout << "\nApellidos: " << endl;
            cin >> apellidos;
            while ( apellidos.length() > g_databasemanager.apellidosLimit || apellidos.length() < 3 )
            {
                cout << "Los apellidos que has introducido tienen " << apellidos.length() << " caracteres" << endl;
                cout << "*Minimo 3 caracteres: " << endl;
                cout << "*Máximo 20 caracteres: " << endl;
                cout << "\nApellidos: " << endl;
                cin >> apellidos;
            } /// END WHILE

            cout << "\nTelefono: " << endl;
            cin >> telefono;
            while ( telefono.length() > g_databasemanager.telefonoLimit || string::npos == telefono.find_first_of("0123456789") || telefono.length() < 6 )
            {
            if(string::npos == telefono.find_first_of("0123456789")) cout << "El telefono que has introducido tiene letras: " << telefono << endl;
            cout << "El telefono que has introducido tiene " << telefono.length() << " caracteres" << endl;
            cout << "*Minimo 3 caracteres: " << endl;
            cout << "*Máximo 10 caracteres: " << endl;
            cout << "*Solo puede contener numeros. " << endl;
            cout << "\nTelefono: " << endl;
            cin >> telefono;
            } /// END WHILE
           g_databasemanager.write(nombre, apellidos, telefono);

        } ///END IF
        else if ( respuesta == "2" )
        {
            g_databasemanager.read();
        }
        else if ( respuesta == "3" )
        {
            g_databasemanager.deleteFile();
        }
        else if ( respuesta == "4" )
        {
            cout << "Escriba lo que quiere buscar: " << endl;
            cin >> busqueda;
            g_databasemanager.search(busqueda);
        } ///END ELSE IF
    } while (respuesta != "5");
}
