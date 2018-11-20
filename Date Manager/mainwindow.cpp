#include <string>
#include <QIntValidator>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "editlinedialog.h"
#include "databaseconnector.h"
#include "configdialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_tabWidget_tabBarClicked(0);
    ui->tabWidget->setCurrentIndex(0);
    QValidator *validator = new QIntValidator(0, 999999999, this);
    ui->lineEdit_Phone->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_btnAdd_clicked()
{
    if(g_databasemanager.write(ui->lineEdit_Name->text().toStdString(), ui->lineEdit_SurNames->text().toStdString(), ui->lineEdit_Phone->text().toStdString() ) == 0)
    {
        QMessageBox::warning(this, "Warning", "The customer were added successful" );
        ui->lineEdit_Name->setText("");
        ui->lineEdit_SurNames->setText("");
        ui->lineEdit_Phone->setText("");
    }
    else if (g_databasemanager.write(ui->lineEdit_Name->text().toStdString(), ui->lineEdit_SurNames->text().toStdString(), ui->lineEdit_Phone->text().toStdString() ) == 1)
    {
        QMessageBox::warning(this, "Warning", "The Name must have at least 3 characters." );

    }
    else if (g_databasemanager.write(ui->lineEdit_Name->text().toStdString(), ui->lineEdit_SurNames->text().toStdString(), ui->lineEdit_Phone->text().toStdString() ) == 2)
    {
        QMessageBox::warning(this, "Warning", "The SurName must have at least 3 characters." );
    }
    else if (g_databasemanager.write(ui->lineEdit_Name->text().toStdString(), ui->lineEdit_SurNames->text().toStdString(), ui->lineEdit_Phone->text().toStdString() ) == 3)
    {
        QMessageBox::warning(this, "Warning", "The Phone must have at least 6 characters." );
    } /// end if
}

void MainWindow::on_actionShow_All_Customers_triggered()
{
    std::string str = g_databasemanager.read();
    QString qstr = QString::fromStdString(str);
    ui->textBrowser->setText(qstr);
    ui->tabWidget->setCurrentIndex(1);
    on_tabWidget_tabBarClicked(1);
}

void MainWindow::on_btnUpdateCustomers_clicked()
{
    on_actionShow_All_Customers_triggered();
}

void MainWindow::on_tabWidget_tabBarClicked(int index) /// Esta funcion se hace para que cada vez que el usuario navegue por los tabs,
                                                      /// los botones se vayan poniendo visibles y el size del form cambie.
{
    if(index == 0)
    {
        MainWindow::setMaximumSize(400,400);
        MainWindow::setMinimumSize(400,400);
        MainWindow::resize(400,400);
        ui->btnUpdateCustomers->setVisible(false);
        ui->btnDeleteAllCustomers->setVisible(false);
        ui->btnDeleteLine->setVisible(false);
        ui->btnEditLine->setVisible(false);
    }
    else if(index == 1)
    {
        MainWindow::setMaximumSize(550,400);
        MainWindow::setMinimumSize(550,400);
        ui->btnUpdateCustomers->setVisible(true);
        ui->btnDeleteAllCustomers->setVisible(true);
        ui->btnDeleteLine->setVisible(true);
        ui->btnEditLine->setVisible(true);
    }
    else if(index == 2)
    {
        MainWindow::setMaximumSize(550,400);
        MainWindow::setMinimumSize(550,400); /// No quiero que el usuario pueda elegir el tamño en este caso.
        ui->btnUpdateCustomers->setVisible(false);
        ui->btnDeleteAllCustomers->setVisible(false);
        ui->btnDeleteLine->setVisible(true);
        ui->btnEditLine->setVisible(true);
    } /// end if
}

void MainWindow::on_btnDeleteAllCustomers_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("You'll delete all data,files.");
    msgBox.setInformativeText("Are you sure?");
    msgBox.setStandardButtons(QMessageBox::YesAll | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::YesAll);
    int ret = msgBox.exec();
    if(ret == QMessageBox::YesAll)
    {
         g_databasemanager.deleteFile();
    }
    msgBox.close();
}

QString MainWindow::on_textBrowser_cursorPositionChanged()
{
     QString line;
     QTextCursor cur = ui->textBrowser->textCursor();
     cur.select(QTextCursor::LineUnderCursor);
     ui->textBrowser->setTextCursor(cur);
     line = cur.selectedText();

     return line;
}

void MainWindow::on_btnDeleteLine_clicked()
{
    std::string line;
    if(ui->tabWidget->currentIndex() == 1)
    {
        line = on_textBrowser_cursorPositionChanged().toStdString();
    }
    else if(ui->tabWidget->currentIndex() == 2)
    {
        line = on_textBrowser_2_cursorPositionChanged().toStdString();
    } /// enf if

    if(line == "We could not find what you are looking for!")
    {
        QMessageBox::warning(this, "Warning", "You can't delete that line - . -" );
    }
    else if(line != "")
    {
        g_databasemanager.deleteLine( line);
    } else {
        QMessageBox::warning(this, "Warning", "Please select a line before!" );
    } /// end if

    if( ui->tabWidget->currentIndex() == 1 )
    {
        on_actionShow_All_Customers_triggered();
    } else {

    }
}

void MainWindow::on_btnSearch_clicked()
{
    std::string line = ui->lineEdit_Search->text().toStdString();
    QString fullText = QString::fromStdString(g_databasemanager.search(line));
    ui->textBrowser_2->setText(fullText);
    if(g_databasemanager.lineFound == false) ui->textBrowser_2->setText("We could not find what you are looking for!");
}

void MainWindow::on_tabWidget_currentChanged(int)
{
    ui->textBrowser_2->setText("");
    ui->lineEdit_Search->setText("");
}

void MainWindow::on_actionAdd_Customer_triggered()
{
    ui->tabWidget->setCurrentIndex(0);
    on_tabWidget_tabBarClicked(0);
}

void MainWindow::on_actionSearch_a_Customer_triggered()
{

    ui->tabWidget->setCurrentIndex(2);
    on_tabWidget_tabBarClicked(2);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionDelete_All_Customers_triggered()
{
    on_btnDeleteAllCustomers_clicked();
}

QString MainWindow::on_textBrowser_2_cursorPositionChanged()
{
    QString line;
    QTextCursor cur = ui->textBrowser_2->textCursor();
    cur.select(QTextCursor::LineUnderCursor);
    ui->textBrowser_2->setTextCursor(cur);
    line = cur.selectedText();

    return line;
}

void MainWindow::on_btnEditLine_clicked()
{
    std::string line;

    if(ui->tabWidget->currentIndex() == 2)
    {
        line = on_textBrowser_2_cursorPositionChanged().toStdString();
    } else {
        line = on_textBrowser_cursorPositionChanged().toStdString();
    }

    if(line != "")
    {

        EditLineDialog editlinedialog;
        editlinedialog.setModal(true);
        editlinedialog.setline(QString::fromStdString(line));
        editlinedialog.exec();
        if(editlinedialog.confirm && editlinedialog.getline() != QString::fromStdString(line))
        {
            g_databasemanager.editLine(line, editlinedialog.getline().toStdString());
            ui->lineEdit_Search->setText("");
            on_btnSearch_clicked();

        } /// end if

    } else {
        QMessageBox::warning(this, "Warning", "Please select a line before!" );
    } /// end if
    if( ui->tabWidget->currentIndex() == 1 )
    {
        on_actionShow_All_Customers_triggered();
    } else {

    }
}

void MainWindow::on_lineEdit_Search_textChanged()
{
    on_btnSearch_clicked();
}

void MainWindow::on_btnConfigDataBase_clicked()
{
    ConfigDialog configdialog;
    configdialog.setModal(true);
    configdialog.exec();
    if (configdialog.on_btnConfirm_clicked() == 1)
    {
            g_databasemanager.pathdatabase = configdialog.getDatabaseName().toStdString();
    }
}
