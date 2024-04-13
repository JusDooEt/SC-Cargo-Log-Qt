#ifndef TRADELOG_H
#define TRADELOG_H

#include <QWidget>
#include <QDateTime>
#include "selldialog.h"

struct TradeRun
{
    QDateTime date;
    QDateTime runTime;
    QString   ship;
    double    profit;
    double    profitPerMin;
    Cargo*    cargoAr;
};

namespace Ui {
class TradeLog;
}

class TradeLog : public QWidget
{
    Q_OBJECT

public:
    explicit TradeLog(QWidget *parent = nullptr);
    ~TradeLog();

private:
    Ui::TradeLog *ui;
};

#endif // TRADELOG_H
