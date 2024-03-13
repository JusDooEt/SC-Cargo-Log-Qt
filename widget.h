#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

struct Ship{
    QString name;
    int     cargoCap;
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public slots:
    void updateTimer();

private:
    Ui::Widget *ui;
    Ship* selectedShip;
    double startingBal;
    double currentBal;
    bool   runStopWatch;
    int    hr;
    int    min;
    int    sec;
    QTimer* timer;

private slots:
    void on_shipNamelineEdit_returnPressed();
    void on_startBalDoubleSpinBox_valueChanged(double arg1);
    void on_beginButton_clicked();
    void on_endButton_clicked();
};
#endif // WIDGET_H
