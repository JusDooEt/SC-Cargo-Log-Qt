#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H


#include <QDialog>
#include <QtSql/QtSql>
#include <QMessageBox>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent, const QSqlDatabase DBConnection);
    ~RegisterDialog();

private slots:

    void onUserEdited();
    void onEmailEdited();
    void onConfirmPassEdited();
    void onUpdateVerifyLabel();
    void on_cancelButton_clicked();

    void on_registerButton_clicked();

private:
    Ui::RegisterDialog *ui;
    const QSqlDatabase DBConnection;
    bool validEmail;
    bool validUser;
    bool validPassword;
};

#endif // REGISTERDIALOG_H
