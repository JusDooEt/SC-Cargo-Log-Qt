#ifndef WIDGET_H
#define WIDGET_H

#include <QDialog>
#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QListWidget>
#include <QtSql/QSql>
#include <QSqlDatabase>
#include "buyerrordialog.h"
#include "sellalldialog.h"
#include "shipList.h"
#include "selldialog.h"
#include "log.h"
#include "statscreen.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent, const int userID);
    ~Widget();


private:
    const int USER_ID;

    QSqlDatabase  DBConnection;
    Ui::Widget*         ui;
    BuyErrorDialog*     cargoBuyError;
    SellAllDialog*      sellAllDialog;
    SellDialog*         sellDialog;
    QTimer*             timer;
    ShipList            shipList;
    std::vector<Cargo>  cargoHold;
    Cargo*              cargoSellPtr;
    //QFile               File;
    //QTextStream         stream;
    double              startingBal;
    double              currentBal;
    bool                runStopWatch;
    bool                sellAll;
    bool                sellButtonEnabled;
    int                 routeID;
    int                 shipIndex;
    int                 cargoIndex;
    int                 hr;
    int                 min;
    int                 sec;
    int                 amountPurchased;
    double              creditsSpent;
    double              creditsEarned;
    double              totalValue;
    double              sellValue;
    double              profit;
    SortType            sort;


    void loadShipCombo();
    void addTransaction(Cargo* item, int type);
signals:
    void shipChanged(int index);
    void shipStorageChanged();

public slots:
    void updateTimer();

private slots:
    void on_startBalDoubleSpinBox_valueChanged(double arg1);
    void on_beginButton_clicked();
    void on_endButton_clicked();
    void on_buyButton_clicked();
    //void on_sellAllButton_clicked();
    //void on_shipComboBox_currentIndexChanged(int index);
    void updateShip(int index);
    //void on_cargoHoldListWidget_currentRowChanged(int currentRow);
    void on_cargoNamelineEdit_textEdited(const QString &arg1);
    void on_cargoHoldListWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_sellButton_clicked();
    void cargoSellAccepted();
    void updateShipStorage();
    void profitSent(const double sentProfit);

    //void on_pushButton_clicked();
    void on_cargoSortButton_clicked();
    void on_shipComboBox_activated(int index);
    void on_nameSortButton_clicked();
    void on_tradeHistoryButton_clicked();
};
#endif // WIDGET_H
