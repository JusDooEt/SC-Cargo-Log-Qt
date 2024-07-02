#include "statscreen.h"
#include "qsqlquery.h"
#include "ui_statscreen.h"

StatScreen::StatScreen(QWidget *parent, const QSqlDatabase DBConnection, const int ROUTE_ID)
    : QDialog(parent)
    , ui(new Ui::StatScreen)
    , DBConnection(DBConnection)
    , ROUTE_ID(ROUTE_ID)
{
    ui->setupUi(this);

    QString queryStr;
    queryFindRoute = new QSqlQuery(DBConnection);
    queryStr = "SELECT * FROM routes WHERE routeID='" + QString::number(ROUTE_ID) + "';";

    if(queryFindRoute->prepare(queryStr))
    {
        if (queryFindRoute->exec())
        {
            qDebug() << "Route Stats Found";
        }
        else
        {
            qDebug() << "Failed to execute query";
        }
    }
    else
    {
        qDebug() << "Failed to prepare query";
    }

    if(queryFindRoute->next())
    {
        getShip();
        getCapacity();
        getDuration();
        getStartingBal();
        getProfit();
    }

}


StatScreen::~StatScreen()
{
    delete ui;
    delete queryFindRoute;
}

void StatScreen::getShip()
{
    shipID = queryFindRoute->value("shipID").toString();
    ui->editShipLabel->setText(shipID);
}

void StatScreen::getCapacity()
{
    QSqlQuery queryFindShip(DBConnection);
    QString queryStr;

    queryStr = "SELECT * FROM ships WHERE shipID='" + shipID + "';";

    if(queryFindShip.prepare(queryStr))
    {
        if (queryFindShip.exec())
        {
            qDebug() << "Ship Stats Found";
        }
        else
        {
            qDebug() << "Failed to execute query";
        }
    }
    else
    {
        qDebug() << "Failed to prepare query";
    }

    if(queryFindShip.next())
    {
        ui->editCapacityLabel->setText(queryFindShip.value("capacity").toString() + " SCU");
    }
}

void StatScreen::getDuration()
{
    duration = queryFindRoute->value("duration").toDouble();
    qDebug() << "duration as double: " << duration;
    ui->editDurLabel->setText(queryFindRoute->value("duration").toString());
}

void StatScreen::getStartingBal()
{
    startingBal = queryFindRoute->value("startingBalance").toDouble();
    ui->editStartBalLabel->setText(QString("%1 aUEC").arg(startingBal, 0, 'f', 2));
}

void StatScreen::getProfit()
{
    profit = queryFindRoute->value("profit").toDouble();
    ui->editProfitLabel->setText(QString("%1 aUEC").arg(profit, 0, 'f', 2));
}

void StatScreen::sendCargoPurchased(int amount)
{
    cargoPurchased = amount;
    ui->editCargoPurLabel->setText(QString::number(cargoPurchased) + " SCU");
}

/*void StatScreen::sendCargoSold(int amount)
{
    cargoSold = amount;
    ui->editCargoSoldLabel->setText(QString::number(cargoSold) + " SCU");
}

void StatScreen::sendCargoRemaining(int amount)
{
    cargoRemaining = amount;
    ui->editCargoRemLabel->setText(QString::number(cargoRemaining) + " SCU");
}
*/

void StatScreen::sendAmountSpent(double amount)
{
    amountSpent = amount;
    ui->editAmountSpentLabel->setText(QString("%1 aUEC").arg(amountSpent, 0, 'f', 2));
}

void StatScreen::sendAmountRecieved(double amount)
{
    amountRecieved = amount;
    ui->editAmountRecLabel->setText(QString("%1 aUEC").arg(amountRecieved, 0, 'f', 2));
}






