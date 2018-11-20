#include <QString>
#include <stdio.h>
#include <iostream>
#include <QMessageBox>
#include <string>
#include <fstream>
#include "databasemanager.h"
#include <databaseconnector.h>
#include <QTextStream>
#include <QFile>

using namespace std;

void DatabaseManager::removeAndRename(const char * p, std::string opcion)
{
    if (remove(p) == -1)
    {  // remove() returns -1 on error
         if(!g_databasemanager.guiMode) cerr << "\nRemove function || Error: " << strerror(errno) << endl;
         else QMessageBox::warning(g_databasemanager.mainWindow, "Warning", strerror(errno) );
    }
    if(rename("temp.txt", p) == -1)
    {
        cerr << "Rename function || Error: " << strerror(errno) << endl;
    } else {
        if(g_databasemanager.guiMode)
        {
            if(opcion == "deleteLine") QMessageBox::warning(g_databasemanager.mainWindow, "Warning", "The line was sucesfully deleted!" );
            else QMessageBox::warning(g_databasemanager.mainWindow, "Warning", "The line was sucesfully edited!" );
        } else {
            if(opcion == "deleteLine") cout << "The line was sucesfully deleted!" << endl;
            else cout << "The line was sucesfully deleted!" << endl;
        }
    }
}

void DatabaseManager::deleteLine(std::string deleteLine) {
    std::string line;
    std::ifstream fin;

    fin.open(g_databasemanager.pathdatabase);
    std::ofstream temp;
    temp.open("temp.txt");

    while (getline(fin, line))
    {
        if (line != deleteLine) // escribe todo menos la linea a buscar.
            temp << line << std::endl;
    }

    temp.close();
    fin.close();

    const char * p = g_databasemanager.pathdatabase.c_str(); // requiero convertirlo para usar las funciones de abajo
    removeAndRename(p, "deleteLine");
}

void DatabaseManager::editLine(std::string oldLine, std::string newLine) {
    std::string line;
    std::ifstream fin;

    fin.open(g_databasemanager.pathdatabase);
    std::ofstream temp;
    temp.open("temp.txt");

    while (getline(fin, line))
    {
        if (line == oldLine)
        {
            line = newLine;
        }
        temp << line << std::endl;
    }

    temp.close();
    fin.close();

    const char * p = g_databasemanager.pathdatabase.c_str(); // requiero convertirlo para usar las funciones de abajo

    removeAndRename(p, "editLine");
}

int DatabaseManager::deleteFile()
{
    if( remove(g_databasemanager.pathdatabase.c_str( )) !=0 )
    {
        if(g_databasemanager.guiMode) QMessageBox::warning(g_databasemanager.mainWindow, "Warning", "Error deleting file" );
        else cout <<"Error deleting file" << endl;
        return 1;
    } else {
        if(g_databasemanager.guiMode)QMessageBox::warning(g_databasemanager.mainWindow, "Warning", "File successfully deleted" );
        else cout << "File successfully deleted" << endl;
        return 0;
    }
}

string DatabaseManager::read()
{
    string line;
    QString fullText;
    ifstream myfile (g_databasemanager.pathdatabase.c_str());

    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            if (g_databasemanager.guiMode)
            {
                fullText += QString::fromUtf8(line.c_str()) + '\n' + '\n';

            } else {
                cout << line << '\n';
            }
        }

    } else {
        if(g_databasemanager.guiMode == false)
        {
            cout << "There's an error opening the file.";
        } else {
            QMessageBox::warning (g_databasemanager.mainWindow, "Warning", "There's no file to read!" );
        }
    }

    myfile.close();
    return fullText.toStdString();
}

string DatabaseManager::search(string texto)
{
        ifstream archivo;
        string line {""};
        string newLine;
        size_t pos;
        string fullText {""};
        string respuesta;
        bool algoEncontrado = false;

        archivo.open(g_databasemanager.pathdatabase);
        if(archivo.is_open())
        {
            while(archivo.peek() != EOF)
            {
                getline(archivo, line);
                pos = line.find(texto);
                if(pos!=string::npos) // el string pos hace return si el string es encontrado
                {
                    if(g_databasemanager.guiMode)
                    {

                        fullText += line + '\n';
                        g_databasemanager.lineFound = true;
                        cout << fullText << endl;

                    } else {
                        cout << "Line found: -" << line << endl;
                        cout << "-Remove the line:  Press (R)." << endl;
                        cout << "-Edit the line:  Press (E)." << endl;
                        cout << "-Continue searching:  Press (C)." << endl;
                        cin >> respuesta;
                        if ( respuesta == "R" || respuesta == "r")
                        {
                            g_databasemanager.deleteLine(line);
                        }
                        else if ( respuesta == "E" || respuesta == "e")
                        {
                            cout << "Now, write that you want the line to be: " << endl;
                            cin >> newLine;
                            cout << line;
                            g_databasemanager.editLine(line, newLine);
                        }
                        algoEncontrado = true;
                    }
                }else{
                    if(fullText == "") g_databasemanager.lineFound = false;
                } /// end if

            } /// END WHILE
            if(!algoEncontrado && g_databasemanager.guiMode == false) cout << "\nNo se ha encontrado lo que buscabas!" << endl;
        } else {
            cout << "\nEl archivo no existe." << endl;
        }/// end if

        archivo.close();
        return fullText;
}

int DatabaseManager::write(string nombre, string apellidos, string telefono)
{
    ofstream archivo;
    time_t now;
    struct tm nowLocal;
    now = time(nullptr);
    nowLocal = *localtime(&now);

    archivo.open(g_databasemanager.pathdatabase, ios::app);

    if(nombre.length() < 3)
    {
        return 1;
    }
    else if(apellidos.length() < 3)
    {
        return 2;
    }
    else if(telefono.length() < 6)
    {
        return 3;
    }/// Esto es para que nos haga un return y no nos deje introducir menos de X caracteres.
    else {
        archivo << nowLocal.tm_mday << "/" << nowLocal.tm_mon+1 << "/" << nowLocal.tm_year+1900
        << " " << nowLocal.tm_hour << ":" << nowLocal.tm_min << ":" << nowLocal.tm_sec << "\t"<<
        ///Estas lineas, 20,21 simplemente escriben la fecha y hora actuales nada más.

        nombre << " " << apellidos << " " << telefono << endl;
        ///Aqui es donde escribimos los datos.

        archivo.close();
        return 0;
    }
}
