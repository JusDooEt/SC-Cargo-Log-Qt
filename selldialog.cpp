#include "selldialog.h"
#include "ui_selldialog.h"

SellDialog::SellDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SellDialog)
{
    ui->setupUi(this);
}

SellDialog::SellDialog(QWidget *parent, Cargo currentCargo, Cargo cargoSold)
    : QDialog(parent)
    , ui(new Ui::SellDialog)
{
    ui->setupUi(this);
    //*cargoSoldPtr = cargoSold;
    //*currentCargoPtr = currentCargo;
    ui->editCargoNameLabel->setText(cargoSold.name);
    ui->editCargoAmountLabel->setText(QString::number(cargoSold.amount));
    ui->editSellForLabel->setText(QString("%1 aUEC").arg(cargoSold.value, 0, 'f', 2));
    ui->editProfitLabel->setText(QString("%1 aUEC").arg((cargoSold.pricePerUnit * cargoSold.amount) - (currentCargo.pricePerUnit * cargoSold.amount), 0, 'f', 2));
}

SellDialog::~SellDialog()
{
    delete ui;
}

void SellDialog::on_buttonBox_accepted()
{
    emit sell();
    close();
}


void SellDialog::on_buttonBox_rejected()
{
    close();
}

