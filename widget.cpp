#include "widget.h"
#include "./ui_widget.h"


//Constructor
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Set up load up state
    ui->cargoNamelineEdit->setDisabled(true);
    ui->priceDoubleSpinBox->setDisabled(true);
    ui->amountSpinBox->setDisabled(true);
    ui->buyButton->setDisabled(true);
    ui->sellButton->setDisabled(true);
    ui->sellAllButton->setDisabled(true);
    ui->endButton->setDisabled(true);

    // ui->currentBalanceLabel->setTextFormat(Qt::FixedNotation)

    // Initialize Ship Combo Box
    loadShipCombo();
    shipIndex = 2;  // C2 Hercules
    ui->shipComboBox->setCurrentIndex(shipIndex);
    ui->amountSpinBox->setMaximum((shipList.getCargoCap(shipIndex) - shipList.getCurrentCap(shipIndex)) * 100);

    // Initialize editShipNameLabel
    ui->editShipNameLabel->setText(ui->shipComboBox->currentText());

    // Initialize editCargoNumLabel
    ui->editCapcityNumLabel->setText(QString::number(shipList.getCurrentCap(2)) +
                                     " / " + QString::number(shipList.getCargoCap(2)) + " SCU");
    // Initialize Ship Object
//    selectedShip = new Ship;
//    selectedShip->name = ui->shipNamelineEdit->text();
//    selectedShip->cargoCap = ui->cargoCapSpinBox->value();
//    selectedShip->currentCap = 0;

    runStopWatch = false;
    sellAll      = false;
    sellButtonEnabled = false;
    totalValue = 0;
    cargoSellPtr = nullptr;
    cargoBuyError = nullptr;
    sellAllDialog = nullptr;
    sellDialog = nullptr;

    hr = 00;
    min = 00;
    sec = 00;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::updateTimer);
    //timer->start(1000);

    //For testing purposes

    startingBal = 10000000;
    currentBal  = startingBal;
    ui->startBalDoubleSpinBox->setValue(startingBal);
    ui->editCurrentBalanceLabel->setText(QString("%1 aUEC").arg(currentBal, 0, 'f', 2));

    connect(this, &Widget::shipStorageChanged, this, &Widget::updateShipStorage);
    connect(this, &Widget::shipChanged, this, &Widget::updateShip);
    //connect(ui->cargoHoldListWidget, &QListWidget::itemDoubleClicked, this)
}

//Deconstructor
Widget::~Widget()
{
    delete ui;
    delete timer;
    delete cargoSellPtr;
//    delete selectedShip;

}


void Widget::profitSent(const double sentProfit)
{
    profit += sentProfit;
    currentBal = startingBal + profit;
    sellValue = totalValue + profit;
//    selectedShip->currentCap = 0;
    shipList.setCurrentCap(shipIndex, 0);
    totalValue = 0;
    ui->editCapcityNumLabel->setText(QString::number(shipList.getCurrentCap(shipIndex)) +
                                     " / " + QString::number(shipList.getCargoCap(shipIndex)) + " SCU");
    ui->editCurrentBalanceLabel->setText(QString("%1 aUEC").arg(currentBal, 0, 'f', 2));
    ui->editProfitLabel->setText(QString("%1 aUEC").arg(profit, 0, 'f', 2));
    ui->editValueLabel->setText(QString("%1 aUEC").arg(totalValue, 0, 'f', 2));
    ui->sellAllButton->setDisabled(true);
    ui->cargoHoldListWidget->clear();
    ui->amountSpinBox->setMaximum((shipList.getCargoCap(shipIndex) - shipList.getCurrentCap(shipIndex)) * 100);
    //reset cargoHoldProgressBar
    ui->cargoHoldProgressBar->setValue(100);
    cargoHold.clear();
}

void Widget::loadShipCombo()
{
    //shipList.getList();
    std::vector<Ship*> list;
    int count;

    list = shipList.getList();
    count = shipList.getShipCount();
    ui->shipComboBox->setMaxCount(count);
    for(int i = 0; i < count; i++)
    {
        ui->shipComboBox->addItem(list[i]->make + ", " + list[i]->model);
    }
}

void Widget::updateTimer()
{
    sec++;

    if(sec == 60)
    {
        min++;
        sec = 0;
    }

    if(min == 60)
    {
        hr++;
        min = 0;

    }

    ui->editHrLabel->setText(hr < 10 ? "0" + QString::number(hr):QString::number(hr));
    ui->editMinLabel->setText(min < 10 ? "0" + QString::number(min) : QString::number(min));
    ui->editSecLabel->setText(sec < 10 ? "0" + QString::number(sec) : QString::number(sec));
}



// If startBalDoubleSpinBox value is changed:
//      store current value in startingBal
void Widget::on_startBalDoubleSpinBox_valueChanged(double arg1)
{
    startingBal = ui->startBalDoubleSpinBox->value();
    currentBal = startingBal;
    ui->editCurrentBalanceLabel->setText(QString("%1 aUEC").arg(currentBal, 0, 'f', 2));
    // qDebug() << "startingBal = " << startingBal;
    // qDebug() << "CurrentBal = " << currentBal;
}


void Widget::on_beginButton_clicked()
{
    // Ui assest formatting
    ui->endButton->setDisabled(false);

    ui->startBalDoubleSpinBox->setDisabled(true);
    ui->beginButton->setDisabled(true);
    ui->cargoNamelineEdit->setDisabled(false);
    ui->priceDoubleSpinBox->setDisabled(false);
    ui->amountSpinBox->setDisabled(false);
    ui->buyButton->setDisabled(false);
    ui->shipComboBox->setDisabled(true);

    // reset clock values;
    hr = 0;
    min = 0;
    sec = 0;
    ui->editHrLabel->setText(hr < 10 ? "0" + QString::number(hr):QString::number(hr));
    ui->editMinLabel->setText(min < 10 ? "0" + QString::number(min) : QString::number(min));
    ui->editSecLabel->setText(sec < 10 ? "0" + QString::number(sec) : QString::number(sec));

    //reset edit labels and reinitialize values
    profit = 0;
    ui->editProfitLabel->setText(QString("%1 aUEC").arg(profit, 0, 'f', 2));


    // start the stop watch
    timer->start(1000);

    // File.setFileName("CargoLog.txt");
    // if (!File.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    // {
    //     qDebug() << "open error" << File.OpenError;
    //     return;
    // }

    // stream.setDevice(&File);
    // stream << "Ship Name: " << shipList.getName(shipIndex);
}


void Widget::on_endButton_clicked()
{
    ui->beginButton->setDisabled(false);
    ui->startBalDoubleSpinBox->setDisabled(false);
    ui->beginButton->setDisabled(false);

    ui->cargoNamelineEdit->setDisabled(true);
    ui->priceDoubleSpinBox->setDisabled(true);
    ui->amountSpinBox->setDisabled(true);
    ui->buyButton->setDisabled(true);
    ui->endButton->setDisabled(true);

    // stop the stop watch
    timer->stop();
    startingBal = currentBal;
    ui->startBalDoubleSpinBox->setValue(startingBal);
    //File.close();
}


void Widget::on_buyButton_clicked()
{
    if(ui->cargoNamelineEdit->isModified())
    {
        bool valid = false;


        QString cargoDesc = "";
        QString name = ui->cargoNamelineEdit->text();
        double pricePerUnit = ui->priceDoubleSpinBox->value();
        int amount = ui->amountSpinBox->value();
        double value = amount * pricePerUnit;

       valid = (ceil(amount/100) <= (shipList.getCargoCap(shipIndex) - shipList.getCurrentCap(shipIndex)) &&
                 value  <= currentBal && ui->priceDoubleSpinBox->value() > 0 && ui->amountSpinBox->value() > 0);

        if(!valid)
        {
            QApplication::beep();
            cargoBuyError = new BuyErrorDialog(this);

            cargoBuyError->setWindowModality(Qt::WindowModality::ApplicationModal);
            cargoBuyError->show();

            return;
        }

        cargoHold.push_back(Cargo(name, pricePerUnit, value, amount));

        currentBal -= value;
        totalValue += value;
        shipList.setCurrentCap(shipIndex, shipList.getCurrentCap(shipIndex) + (amount / 100));

        ui->editCurrentBalanceLabel->setText(QString("%1 aUEC").arg(currentBal, 0, 'f', 2));
        ui->editValueLabel->setText(QString("%1 aUEC").arg(totalValue, 0, 'f', 2));

        // ui->editCapcityNumLabel->setText(QString::number(shipList.getCurrentCap(shipIndex)) + " / " + QString::number(shipList.getCargoCap(shipIndex)) + " SCU");
        // ui->cargoHoldProgressBar->setValue(100-(((double)shipList.getCurrentCap(shipIndex) / shipList.getCargoCap(shipIndex)) * 100));
        emit shipStorageChanged();
        cargoDesc = (name +
                    "\nAmount: " + QString::number(amount) +
                    "\nPrice per UNIT: " + QString::number(pricePerUnit) + " aUEC"
                    "\nValue: " + QString("%1 aUEC").arg(value, 0, 'f', 2) +
                    "\n");

        ui->cargoHoldListWidget->addItem(cargoDesc);
        ui->amountSpinBox->setMaximum((shipList.getCargoCap(shipIndex) - shipList.getCurrentCap(shipIndex)) * 100);
        // if(!ui->sellButton->isEnabled())
        //     ui->sellButton->setEnabled(true);
        if(!ui->sellAllButton->isEnabled())
            ui->sellAllButton->setEnabled(true);
    }

}




void Widget::on_sellAllButton_clicked()
{
    sellAllDialog = new SellAllDialog(this, startingBal, currentBal);
    sellAllDialog->show();

    connect(sellAllDialog, &SellAllDialog::sendProfit, this, &Widget::profitSent);
}




void Widget::on_shipComboBox_currentIndexChanged(int index)
{
    shipIndex = index;
    emit shipChanged(index);
}

void Widget::updateShip(int index)
{
    ui->editShipNameLabel->setText(shipList.getName(index));
    // ui->editCapcityNumLabel->setText(QString::number(shipList.getCurrentCap(shipIndex)) +
    //                                  " / " + QString::number(shipList.getCargoCap(shipIndex)) + " SCU");
    // ui->amountSpinBox->setMaximum((shipList.getCargoCap(shipIndex) - shipList.getCurrentCap(shipIndex)) * 100);
    emit shipStorageChanged();
}




// void Widget::on_cargoHoldListWidget_currentRowChanged(int currentRow)
// {
//     qDebug() << "currentRow: " << currentRow;
//     qDebug() << "Cargo[" << currentRow << "] name: " << cargoHold[currentRow].name;
//     ui->cargoNamelineEdit->setText(cargoHold[currentRow].name);
//     ui->priceDoubleSpinBox->setValue(cargoHold[currentRow].pricePerUnit);
//     ui->amountSpinBox->setValue(cargoHold[currentRow].amount);
//     ui->amountSpinBox->setMaximum(cargoHold[currentRow].amount);
//     ui->sellButton->setEnabled(true);
// }




void Widget::on_cargoNamelineEdit_textEdited(const QString &arg1)
{
    if(ui->sellButton->isEnabled())
    {
        ui->sellButton->setDisabled(true);
        ui->amountSpinBox->setMaximum(shipList.getCargoCap(shipIndex) - shipList.getCurrentCap(shipIndex));
        ui->amountSpinBox->setValue(shipList.getCargoCap(shipIndex) - shipList.getCurrentCap(shipIndex));
        ui->cargoHoldListWidget->clearSelection();
    }

}


void Widget::on_cargoHoldListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    cargoIndex = ui->cargoHoldListWidget->currentRow();
    qDebug() << "Name: " << cargoHold[cargoIndex].name;
    qDebug() << "Amount: " <<cargoHold[cargoIndex].amount;
    qDebug() << "Price per Unit: " << cargoHold[cargoIndex].pricePerUnit;
    qDebug() << "Value: " << cargoHold[cargoIndex].value;
    ui->amountSpinBox->setMaximum(cargoHold[cargoIndex].amount);
    ui->cargoNamelineEdit->setText(cargoHold[cargoIndex].name);
    ui->priceDoubleSpinBox->setValue(cargoHold[cargoIndex].pricePerUnit);
    ui->amountSpinBox->setValue(cargoHold[cargoIndex].amount);
    ui->sellButton->setEnabled(true);
}


void Widget::on_sellButton_clicked()
{

    QString cargoSellName;
    double  cargoSellPrice;
    double  cargoSellValue;
    int     cargoSellAmount;


    cargoSellName = ui->cargoNamelineEdit->text();
    cargoSellPrice = ui->priceDoubleSpinBox->value();
    cargoSellAmount = ui->amountSpinBox->value();
    cargoSellValue = cargoSellPrice * cargoSellAmount;
    if(cargoSellPtr != nullptr)
    {
        delete cargoSellPtr;
        cargoSellPtr = nullptr;
        qDebug() << "Sell obj deleted";
    }
    cargoSellPtr = new Cargo(cargoSellName, cargoSellPrice, cargoSellValue, cargoSellAmount);
    qDebug() << "New sellCargo obj created";

    sellDialog = new SellDialog(this, cargoHold[cargoIndex], *cargoSellPtr);
    sellDialog->show();
    connect(sellDialog, &SellDialog::sell, this, &Widget::cargoSellAccepted);
}

void Widget::cargoSellAccepted()
{
    if(ui->amountSpinBox->value() == cargoHold[cargoIndex].amount)
    {
        profit += cargoSellPtr->value - cargoHold[cargoIndex].value;
        cargoHold.erase(cargoHold.begin() + cargoIndex);
    }
    else
    {
        profit += cargoSellPtr->value - (cargoHold[cargoIndex].pricePerUnit * cargoSellPtr->amount);
        cargoHold[cargoIndex].amount -= cargoSellPtr->amount;
        cargoHold[cargoIndex].value = cargoHold[cargoIndex].amount * cargoHold[cargoIndex].pricePerUnit;
    }
    ui->cargoHoldListWidget->clear();

    for(int i = 0; i < cargoHold.size(); i++)
    {
        ui->cargoHoldListWidget->addItem(cargoHold[i].name +
                                         "\nAmount: " + QString::number(cargoHold[i].amount) +
                                         "\nPrice per UNIT: " + QString::number(cargoHold[i].pricePerUnit) + " aUEC"
                                                                                                             "\nValue: " + QString("%1 aUEC").arg(cargoHold[i].value, 0, 'f', 2) +
                                         "\n");
    }

    shipList.setCurrentCap(shipIndex, shipList.getCurrentCap(shipIndex) - ceil(cargoSellPtr->amount / 100));
    emit shipStorageChanged();

    //Edit Profit label
    ui->editProfitLabel->setText(QString("%1 aUEC").arg(profit, 0, 'f', 2));

    //reset cargo input compenents
    ui->cargoNamelineEdit->clear();
    ui->amountSpinBox->setValue(0);
    ui->priceDoubleSpinBox->setValue(0);
    ui->sellButton->setDisabled(true);
}

void Widget::updateShipStorage()
{
    ui->editCapcityNumLabel->setText(QString::number(shipList.getCurrentCap(shipIndex)) +
                                     " / " + QString::number(shipList.getCargoCap(shipIndex)) + " SCU");
    ui->cargoHoldProgressBar->setValue(100-(((double)shipList.getCurrentCap(shipIndex) / shipList.getCargoCap(shipIndex)) * 100));
    ui->amountSpinBox->setMaximum((shipList.getCargoCap(shipIndex) - shipList.getCurrentCap(shipIndex)) * 100);
}

/*
void Widget::on_pushButton_clicked()
{
    shipList.sortByCargo();
    ui->shipComboBox->setDisabled(true);
    qDebug() << 1;
    for(int i = 0; i < shipList.getShipCount(); i++)
        ui->shipComboBox->removeItem(i);
    qDebug() << 2;
    loadShipCombo();
qDebug() << 3;
    ui->shipComboBox->setEnabled(true);
qDebug() << 4;
}
*/

void Widget::on_cargoSortButton_clicked()
{
    setDisabled(true);
    shipList.sortByCargo();
    shipList.printArray(shipList.getList(), shipList.getList().size());
    ui->shipComboBox->setDisabled(true);
    qDebug() << 1;
    for(int i = 0; i < shipList.getShipCount(); i++)
        ui->shipComboBox->removeItem(i);
    qDebug() << 2;
    loadShipCombo();
    qDebug() << 3;
    ui->shipComboBox->setEnabled(true);
    qDebug() << 4;
    setEnabled(true);
}

