#include <string>
#include <QString>
#include <QMessageBox>
#include "editlinedialog.h"
#include "ui_editlinedialog.h"
#include "mainwindow.h"


EditLineDialog::EditLineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditLineDialog)
{
    ui->setupUi(this);

}

EditLineDialog::~EditLineDialog()
{
    delete ui;
}

void EditLineDialog::setline(QString setline)
{
     ui->lineEdit_EditLine->setText(setline);
}

QString EditLineDialog::getline()
{
    return ui->lineEdit_EditLine->text();
}

void EditLineDialog::on_btnConfirm_clicked()
{
   if ( ui->lineEdit_EditLine->text().length() > 75 )
   {
       QMessageBox::warning(this, "Warning", "The line is too long!" );
   } else {
       confirm = true;
       this->close();
   } ///end if
}

void EditLineDialog::on_btnCancel_clicked()
{
    this->close();
}
