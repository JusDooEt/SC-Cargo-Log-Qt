#include "sellalldialog.h"
#include "ui_sellalldialog.h"

SellAllDialog::SellAllDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SellAllDialog)
{
    ui->setupUi(this);
}

SellAllDialog::SellAllDialog(QWidget *parent, const double startBal, double currentBal)
    : QDialog(parent)
    , ui(new Ui::SellAllDialog)
{
    ui->setupUi(this);
    this->startBal = startBal;
    this->currentBal = currentBal;
    ui->editStartBalLabel->setText(QString("%1 aUEC").arg(startBal, 0, 'f', 2));
    ui->editCurrentBalLabel->setText(QString("%1 aUEC").arg(currentBal, 0, 'f', 2));
    profit = currentBal - startBal;
}

SellAllDialog::~SellAllDialog()
{
    delete ui;
}

void SellAllDialog::on_cancelButton_clicked()
{
    close();
}


void SellAllDialog::on_doubleSpinBox_valueChanged(double arg1)
{
    sellPrice = arg1;
    currentBal += sellPrice;
    profit = currentBal - startBal;
    ui->editCurrentBalLabel->setText(QString("%1 aUEC").arg(currentBal, 0, 'f', 2));
    ui->editProfitLabel->setText(QString("%1 aUEC").arg(profit, 0, 'f', 2));
}


void SellAllDialog::on_sellAllButton_clicked()
{

}

