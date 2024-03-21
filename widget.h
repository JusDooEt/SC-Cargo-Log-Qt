#ifndef WIDGET_H
#define WIDGET_H

#include <QDialog>
#include <QWidget>
#include <QDebug>
#include <QTimer>
#include "buyerrordialog.h"
#include "sellalldialog.h"
#include "shipList.h"

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

// struct Ship{
//     QString name;
//     int     cargoCap;
//     int     currentCap;
// };

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
    ShipList            shipList;
    Cargo*              cargoHead;
    double              startingBal;
    double              currentBal;
    bool                runStopWatch;
    bool                sellAll;
    int                 shipIndex;
    int                 hr;
    int                 min;
    int                 sec;
    double              totalValue;
    double              sellValue;
    double              profit;


    void deleteCargoHold();
    void profitSent(const double sentProfit);
    void loadShipCombo();

signals:
    void shipUpdated(int index);

public slots:
    void updateTimer();

private slots:
    void on_startBalDoubleSpinBox_valueChanged(double arg1);
    void on_beginButton_clicked();
    void on_endButton_clicked();
    void on_buyButton_clicked();
    void on_sellAllButton_clicked();
    void on_sellButton_clicked();
    void on_shipComboBox_currentIndexChanged(int index);
    void shipChanged(int index);
};
#endif // WIDGET_H
