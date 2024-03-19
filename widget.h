#ifndef WIDGET_H
#define WIDGET_H

#include <QDialog>
#include <QWidget>
#include <QDebug>
#include <QTimer>
#include "buyerrordialog.h"
#include "sellalldialog.h"
#include <QListWidget>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

struct Cargo{
    QString name;
    double  pricePerUnit;
    double  value;
    int     amount;
    Cargo*  next;
};

struct Ship{
    QString name;
    int     cargoCap;
    int     currentCap;
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private:
    Ui::Widget*         ui;
    BuyErrorDialog*     cargoBuyError;
    SellAllDialog*      sellAllDialog;
    QTimer*             timer;
    Ship*               selectedShip;
    Cargo*              cargoHead;
    double              startingBal;
    double              currentBal;
    bool                runStopWatch;
    bool                sellAll;
    int                 hr;
    int                 min;
    int                 sec;
    double              totalValue;
    double              sellValue;
    double              profit;

    void deleteCargoHold();
    void profitSent(const double sentProfit);


public slots:
    void updateTimer();

private slots:
    void on_shipNamelineEdit_returnPressed();
    void on_startBalDoubleSpinBox_valueChanged(double arg1);
    void on_beginButton_clicked();
    void on_endButton_clicked();
    void on_buyButton_clicked();
    void on_sellAllButton_clicked();

};
#endif // WIDGET_H
