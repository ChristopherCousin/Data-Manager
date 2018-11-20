#include <QApplication>
#include "mainwindow.h"
#include "databasemanager.h"
#include "interfazconsola.h"
#include "databaseconnector.h"


DatabaseManager g_databasemanager;

int main(int argc, char *argv[])
{
    if (argc >= 1)
    {
        QString parameter = QString(argv[1]);
        if(parameter == "gui")
        {
            QApplication a(argc, argv);
            MainWindow w;
            w.show();
            return a.exec();

        }
        else if(parameter == "con")
        {
            g_databasemanager.guiMode = false;
            InterfazConsola interfazConsola;
            interfazConsola.show();
        }
    } /// end if
    return 0;
}
