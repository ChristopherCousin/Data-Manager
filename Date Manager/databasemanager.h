#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "mainwindow.h"


struct DatabaseManager
{
    std::string pathdatabase {"DataBaseExample.txt"};
    bool guiMode{true};
    bool lineFound{false};
    MainWindow *mainWindow{nullptr};
    void removeAndRename(const char * p, std::string opcion);
    void deleteLine( std::string deleteLine);
    void editLine( std::string oldLine, std::string newLine);
    int deleteFile();
    int write(std::string nombre, std::string apellidos, std::string telefono);
    std::string search(std::string texto);
    std::string read();

    int unsigned nombreLimit {20};
    int unsigned apellidosLimit {20};
    int unsigned telefonoLimit {10};
};


#endif // DATABASEMANAGER_H
