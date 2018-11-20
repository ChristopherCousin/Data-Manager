#ifndef EDITLINEDIALOG_H
#define EDITLINEDIALOG_H

#include <QDialog>


namespace Ui {
class EditLineDialog;
}

class EditLineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditLineDialog(QWidget *parent = nullptr);
    ~EditLineDialog();
    void setline(QString);
    QString getline();
    bool confirm = false;

private slots:

    void on_btnConfirm_clicked();
    void on_btnCancel_clicked();

private:
    Ui::EditLineDialog *ui;
};

#endif // EDITLINEDIALOG_H
