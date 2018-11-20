#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "editlinedialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

     void lineSelected (const QString lineselected);
     QString getLineaSelected();

private slots:

    void on_btnAdd_clicked();

    void on_actionShow_All_Customers_triggered();

    void on_btnUpdateCustomers_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_btnDeleteAllCustomers_clicked();

    QString on_textBrowser_cursorPositionChanged();

    void on_btnDeleteLine_clicked();

    void on_btnSearch_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_actionAdd_Customer_triggered();

    void on_actionSearch_a_Customer_triggered();

    void on_actionExit_triggered();

    void on_actionDelete_All_Customers_triggered();

    void on_btnEditLine_clicked();

    void on_lineEdit_Search_textChanged();

    void on_btnConfigDataBase_clicked();

public slots:

    QString on_textBrowser_2_cursorPositionChanged();

private:

    Ui::MainWindow *ui;
    EditLineDialog *editlinedialog;
};

#endif // MAINWINDOW_H
