#include "loginwidget.h"
#include "qsqlquery.h"
#include "ui_loginwidget.h"


LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
{
    // Member Initiializations
    ui->setupUi(this);
    app = nullptr;

    DBConnection = QSqlDatabase::addDatabase("QSQLITE");
    DBConnection.setDatabaseName(QCoreApplication::applicationDirPath() + "/SC-Log.db");

    // Validate Database connection
    if(DBConnection.open())
    {
        qDebug() << "Database Connected";
    }
    else
    {
        qDebug() << "Database not connected";
    }

    // Create a table for users if the database is empty
    if(!DBConnection.tables().size())
    {
        createUserTable();
    }
}

LoginWidget::~LoginWidget()
{
    DBConnection.close();
    delete ui;
}

void LoginWidget::createUserTable()
{
    QSqlQuery createUserTable(DBConnection);
    QString query = "CREATE TABLE users (";
    query += "username TEXT PRIMARY KEY UNIQUE NOT NULL, ";
    query += "email TEXT NOT NULL UNIQUE," ;
    query += "password TEXT NOT NULL);";
    if(createUserTable.prepare(query))
    {
        if(createUserTable.exec())
        {
            qDebug() << "Table Created: " << DBConnection.tables().first();
        }
        else
        {
            qDebug() << "Could not execute query.";
        }
    }
    else
    {
        qDebug() << "Query preperation Unsuccessful.";
    }
}

void LoginWidget::on_register_pushButton_clicked()
{
    this->setDisabled(true);
    RegisterDialog* registerDialog = new RegisterDialog(this, DBConnection);
    registerDialog->show();
    connect(registerDialog, &QDialog::finished, this, [=](){
        qDebug() << "Register Dialog closed";
        this->setEnabled(true);
    });
}


void LoginWidget::on_login_pushButton_clicked()
{
    if(ui->password_lineEdit->text().length() == 0 || ui->username_lineEdit->text().length() == 0)
        return;

    int userID = -1;
    QSqlQuery queryFindUser(DBConnection);
    QString   queryStr;
    QString   username = ui->username_lineEdit->text();
    QString   password = ui->password_lineEdit->text();

    queryStr = "SELECT * FROM users WHERE username='" + username;
    queryStr += "' AND password='" + password + "';";
    if(queryFindUser.prepare(queryStr))
    {
        if (queryFindUser.exec())
        {
            unsigned int userFoundCount = 0;
            while (queryFindUser.next())
            {
                userFoundCount++;
                userID = queryFindUser.value("userID").toInt();
            }

            if (userFoundCount == 1)    // Username and password match
            {

                QMessageBox::information(this, "Login", "Login Successful.");
                this->hide();
                app = new Widget(nullptr, userID);
                app->show();
            }
            else if (userFoundCount == 0)   // Matching username and password were not found
            {
                QMessageBox::information(this, "Login", "Failed to login.\nCheck your username and password.");

            }
            else                            // ERROR
            {
                QMessageBox::information(this, "Login", "Failed to login.\nCheck your username and password.");
                qDebug() << "<ERROR> - Potential Duplicates in Database";
            }
        }
        else
        {
            qDebug() << "<ERROR> - " << QSqlError().text();
        }
    }
    else
    {
        qDebug() << "<ERROR> - " << QSqlError().text();
    }
}


void LoginWidget::on_password_lineEdit_returnPressed()
{
    on_login_pushButton_clicked();
}

