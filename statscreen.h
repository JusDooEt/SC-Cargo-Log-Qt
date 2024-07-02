#ifndef STATSCREEN_H
#define STATSCREEN_H

#include <QDialog>
#include <QtSql/QSql>
#include <QSqlDatabase>

namespace Ui {
class StatScreen;
}

class StatScreen : public QDialog
{
    Q_OBJECT

public:

    explicit StatScreen(QWidget *parent, const QSqlDatabase DBConnection, const int ROUTE_ID);
    ~StatScreen();

private:
    Ui::StatScreen *ui;
    const QSqlDatabase DBConnection;
    const int ROUTE_ID;
    QSqlQuery* queryFindRoute;
    QString shipID;
    double duration;
    int cargoPurchased;
    int cargoSold;
    int cargoRemaining;
    double startingBal;
    double amountSpent;
    double amountRecieved;
    double profit;

private slots:
    void getShip();
    void getCapacity();
    void getDuration();
    void getStartingBal();
    void getProfit();

public slots:
    void sendCargoPurchased(int amount);
    //void sendCargoSold(int amount);
    //void sendCargoRemaining(int amount);
    void sendAmountSpent(double amount);
    void sendAmountRecieved(double amount);
};

#endif // STATSCREEN_H
