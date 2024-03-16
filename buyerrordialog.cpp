#include "buyerrordialog.h"
#include "ui_buyerrordialog.h"

BuyErrorDialog::BuyErrorDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BuyErrorDialog)
{
    ui->setupUi(this);
}

BuyErrorDialog::~BuyErrorDialog()
{
    delete ui;
}

void BuyErrorDialog::on_pushButton_clicked()
{
    close();
}

