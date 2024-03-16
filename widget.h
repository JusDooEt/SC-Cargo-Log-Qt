#ifndef WIDGET_H
#define WIDGET_H

#include <QDialog>
#include <QWidget>
#include <QDebug>
#include <QTimer>

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
    Ui::Widget* ui;
    QDialog*    cargoBuyError;
    QDialog*    sellAllDialog;
    QTimer*     timer;
    Ship*       selectedShip;
    Cargo*      cargoHead;
    double      startingBal;
    double      currentBal;
    bool        runStopWatch;
    bool        sellAll;
    int         hr;
    int         min;
    int         sec;
    double         totalValue;

    void deleteCargoHold();



public slots:
    void updateTimer();

private slots:
    void on_shipNamelineEdit_returnPressed();
    void on_startBalDoubleSpinBox_valueChanged(double arg1);
    void on_beginButton_clicked();
    void on_endButton_clicked();
    void on_buyButton_clicked();
    void onOkButtonClicked();
    void on_sellAllButton_clicked();
    void onNoButtonClicked();
    void onYesButtonClicked();
};
#endif // WIDGET_H
