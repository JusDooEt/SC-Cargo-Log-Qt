#ifndef TRADELOG_H
#define TRADELOG_H

#include <QWidget>

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
