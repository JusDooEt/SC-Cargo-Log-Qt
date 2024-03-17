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
    ui->sellAllButton->setDisabled(true);
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
    sellPrice = ui->doubleSpinBox->value();
    ui->editCurrentBalLabel->setText(QString("%1 aUEC").arg(currentBal + sellPrice, 0, 'f', 2));
    ui->editProfitLabel->setText(QString("%1 aUEC").arg(currentBal + sellPrice - startBal, 0, 'f', 2));
    ui->sellAllButton->setDisabled(false);
}


void SellAllDialog::on_sellAllButton_clicked()
{
    profit = currentBal + sellPrice - startBal;
    emit sendProfit(profit);
    close();
}

