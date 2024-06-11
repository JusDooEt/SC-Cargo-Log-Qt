#include "registerdialog.h"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent,const QSqlDatabase DBConnection)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
    , DBConnection(DBConnection)
{
    ui->setupUi(this);
    validEmail = false;
    validUser = false;
    validPassword = false;
    connect(ui->usernameLineEdit, &QLineEdit::textEdited, this, &RegisterDialog::onUserEdited);
    connect(ui->emailLineEdit, &QLineEdit::textEdited, this, &RegisterDialog::onEmailEdited);
    connect(ui->confirmPassLineEdit, &QLineEdit::textEdited, this, &RegisterDialog::onConfirmPassEdited);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::onUserEdited()
{

    QString username = ui->usernameLineEdit->text();

    if(!username.size())
    {
        return;
    }

    QSqlQuery queryGetUser(DBConnection);
    if(queryGetUser.prepare("SELECT * FROM users WHERE username='" + username + "';"))
    {
        if(queryGetUser.exec())
        {
            int userFoundCount = 0;
            while(queryGetUser.next())
            {
                userFoundCount++;
            }

            if(userFoundCount == 1) // User name was found in database
            {
                validUser = false;
            }
            else if(userFoundCount == 0)
            {
                validUser = true;
            }

            onUpdateVerifyLabel();
        }
    }
}

void RegisterDialog::onEmailEdited()
{
    QString email = ui->emailLineEdit->text();

    if(!email.size())
    {
        return;
    }

    QSqlQuery queryGetEmail(DBConnection);
    if(queryGetEmail.prepare("SELECT * FROM users WHERE email='" + email + "';"))
    {
        if(queryGetEmail.exec())
        {
            int emailFoundCount = 0;
            while(queryGetEmail.next())
            {
                emailFoundCount++;
            }

            if(emailFoundCount == 1) // Email was found in database
            {
                validEmail = false;
            }
            else if(emailFoundCount == 0)
            {
                validEmail = true;
            }

            onUpdateVerifyLabel();
        }
    }
}

void RegisterDialog::onConfirmPassEdited()
{
    if(ui->confirmPassLineEdit->text() == ui->passwordLineEdit->text() && ui->passwordLineEdit->isModified())
    {
        validPassword = true;
    }
    else
    {
        validPassword = false;
    }
    onUpdateVerifyLabel();
}

void RegisterDialog::onUpdateVerifyLabel()
{
    if(validUser)
    {
        ui->userVerifyLabel->setText("Username is available!");
    }
    else
    {
        ui->userVerifyLabel->setText("Username not available");
    }

    if(validPassword)
    {
        ui->passVerifyLabel->setText("Passwords match!");
    }
    else
    {
        ui->passVerifyLabel->setText("Passwords do not match");
    }

    if(validEmail)
    {
        ui->verifyEmailLabel->setText("Valid Email!");
    }
    else
    {
        ui->verifyEmailLabel->setText("This email already has an account.");
    }
}




void RegisterDialog::on_cancelButton_clicked()
{
    close();
}


void RegisterDialog::on_registerButton_clicked()
{
    if(validEmail && validPassword && validUser)
    {
        QString username = ui->usernameLineEdit->text();
        QString email = ui->emailLineEdit->text();
        QString password = ui->confirmPassLineEdit->text();
        QString queryStr = "INSERT INTO users (username, email, password) VALUES('" +
                           username + "', '" + email + "', '" + password + "');";

        QSqlQuery queryInsertUser(DBConnection);
        if(queryInsertUser.prepare(queryStr))
        {
            if(queryInsertUser.exec())
            {
                qDebug() << "User: " << username;
                qDebug() << "Email: " << email;
                qDebug() << "Registed in the database";

                QMessageBox::information(this, "Registered", username + " has been successfully registered!");
            }

        }
        close();
    }
    else
    {
        QMessageBox::information(this, "Failed", "Registration failed. Please check your information.");
    }
}

