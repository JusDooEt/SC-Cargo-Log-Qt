#include "tradelog.h"
#include "ui_tradelog.h"

TradeLog::TradeLog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TradeLog)
{
    ui->setupUi(this);
}

TradeLog::~TradeLog()
{
    delete ui;
}
