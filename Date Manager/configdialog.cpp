#include <QString>
#include "configdialog.h"
#include "ui_configdialog.h"
#include "databaseconnector.h"
#include "QFileDialog"

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);
    ui->ConfigDatabase_lineEdit->setText(QString::fromStdString(g_databasemanager.pathdatabase));
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::putDefaultDatabaseName()
{
    std::string empty = "";
    for (int x = 0; x < 30 ; x++)
    {
        if(ui->ConfigDatabase_lineEdit->text() == QString::fromStdString(empty)) ui->ConfigDatabase_lineEdit->setText("DefaultNameDataBase.txt");
        empty += " ";
    } /// Aqui ponemos un bucle para que vaya sumando espacios y que el campo de nombre de base de datos siempre
      ///  sea DefaultNameBase, en el caso en el que el usuario se deje espacios, ya que eso causaria errores.
}
QString ConfigDialog::getDatabaseName()
{
    return ui->ConfigDatabase_lineEdit->text();
}

void ConfigDialog::on_btnCancel_clicked()
{
    putDefaultDatabaseName();
    this->close();
}

int ConfigDialog::on_btnConfirm_clicked()
{
    putDefaultDatabaseName();
    this->close();
    return 1;
}

void ConfigDialog::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,  ("Open File"));
    ui->ConfigDatabase_lineEdit->setText(fileName);
    putDefaultDatabaseName();
}
