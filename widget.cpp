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
    totalValue = 0;
    cargoHead = nullptr;

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

    connect(this, &Widget::shipUpdated, this, &Widget::shipChanged);
}

//Deconstructor
Widget::~Widget()
{
    delete ui;
    delete timer;
//    delete selectedShip;
    deleteCargoHold();
}

void Widget::deleteCargoHold()
{
    if(cargoHead == nullptr)
    {
        return;
    }

    Cargo* tempPtr;
    while (cargoHead != nullptr)
    {
        tempPtr = cargoHead;
        cargoHead = tempPtr->next;
        delete tempPtr;
        tempPtr = nullptr;
    }
}

void Widget::profitSent(const double sentProfit)
{
    profit = sentProfit;
    currentBal = startingBal + profit;
    startingBal = currentBal;
    sellValue = totalValue + profit;
//    selectedShip->currentCap = 0;
    shipList.setCurrentCap(shipIndex, 0);
    totalValue = 0;
    ui->editCapcityNumLabel->setText(QString::number(shipList.getCurrentCap(shipIndex)) +
                                     " / " + QString::number(shipList.getCargoCap(shipIndex)) + " SCU");
    ui->editCurrentBalanceLabel->setText(QString("%1 aUEC").arg(currentBal, 0, 'f', 2));
    ui->editProfitLabel->setText(QString("%1 aUEC").arg(profit, 0, 'f', 2));
    ui->startBalDoubleSpinBox->setValue(startingBal);
    ui->editValueLabel->setText(QString("%1 aUEC").arg(totalValue, 0, 'f', 2));
    ui->sellAllButton->setDisabled(true);
    ui->cargoHoldListWidget->clear();
    ui->amountSpinBox->setMaximum((shipList.getCargoCap(shipIndex) - shipList.getCurrentCap(shipIndex)) * 100);
    //reset cargoHoldProgressBar
    ui->cargoHoldProgressBar->setValue(100);
    deleteCargoHold();
}

void Widget::loadShipCombo()
{
    shipList.getList();
    std::vector<Ship> list;
    int count;

    list = shipList.getList();
    count = shipList.getShipCount();
    ui->shipComboBox->setMaxCount(count);
    for(int i = 0; i < count; i++)
    {
        ui->shipComboBox->addItem(list[i].make + ", " + list[i].model);
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
}


void Widget::on_buyButton_clicked()
{
    if(ui->cargoNamelineEdit->isModified())
    {
        bool valid = false;

        Cargo* ptr;
        QString cargoDesc = "";
        ptr = new Cargo;
        ptr->name = ui->cargoNamelineEdit->text();
        ptr->pricePerUnit = ui->priceDoubleSpinBox->value();
        ptr->amount = ui->amountSpinBox->value();
        ptr->value = ptr->amount * ptr->pricePerUnit;

       valid = (ceil(ptr->amount/100) <= (shipList.getCargoCap(shipIndex) - shipList.getCurrentCap(shipIndex)) &&
                ptr->value  <= currentBal);

        if(!valid)
        {
            QApplication::beep();
            cargoBuyError = new BuyErrorDialog(this);

            cargoBuyError->setWindowModality(Qt::WindowModality::ApplicationModal);
            cargoBuyError->show();

            return;
        }

        ptr->next = cargoHead;
        cargoHead = ptr;

        currentBal -= cargoHead->value;
        totalValue += cargoHead->value;
        shipList.setCurrentCap(shipIndex, shipList.getCurrentCap(shipIndex) + (cargoHead->amount / 100));

        ui->editCurrentBalanceLabel->setText(QString("%1 aUEC").arg(currentBal, 0, 'f', 2));
        ui->editValueLabel->setText(QString("%1 aUEC").arg(totalValue, 0, 'f', 2));
        ui->editCapcityNumLabel->setText(QString::number(shipList.getCurrentCap(shipIndex)) + " / " + QString::number(shipList.getCargoCap(shipIndex)) + " SCU");
        ui->cargoHoldProgressBar->setValue(100-(((double)shipList.getCurrentCap(shipIndex) / shipList.getCargoCap(shipIndex)) * 100));
        cargoDesc = (cargoHead->name +
                    "\nAmount: " + QString::number(cargoHead->amount) +
                    "\nPrice per UNIT: " + QString::number(cargoHead->pricePerUnit) + " aUEC"
                    "\nValue: " + QString("%1 aUEC").arg(cargoHead->value, 0, 'f', 2) +
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


void Widget::on_sellButton_clicked()
{
    Cargo* ptr;
    QString cargoDesc = "";
    ptr = new Cargo;
    ptr->name = ui->cargoNamelineEdit->text();
    ptr->pricePerUnit = ui->priceDoubleSpinBox->value();
    ptr->amount = ui->amountSpinBox->value();
    ptr->value = ptr->amount * ptr->pricePerUnit;
    //bool valid = (ceil(ptr->amount/100) <= (selectedShip->cargoCap - selectedShip->currentCap) &&
    //         ptr->value  <= currentBal);
}


void Widget::on_shipComboBox_currentIndexChanged(int index)
{
    shipIndex = index;
    emit shipUpdated(index);
}

void Widget::shipChanged(int index)
{
    ui->editShipNameLabel->setText(shipList.getName(index));
    ui->editCapcityNumLabel->setText(QString::number(shipList.getCurrentCap(index)) +
                                     " / " + QString::number(shipList.getCargoCap(index)) + " SCU");
    ui->amountSpinBox->setMaximum((shipList.getCargoCap(shipIndex) - shipList.getCurrentCap(shipIndex)) * 100);
}

