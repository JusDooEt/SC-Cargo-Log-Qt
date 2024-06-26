#include "widget.h"
#include "./ui_widget.h"
#include "qsqlquery.h"

//Constructor
Widget::Widget(QWidget *parent, const int userID)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , USER_ID(userID)
{
    ui->setupUi(this);

    // Debug USER_ID
    qDebug() << "USER_ID = " << USER_ID;
    // Set up load up state
    ui->cargoNamelineEdit->setDisabled(true);
    ui->priceDoubleSpinBox->setDisabled(true);
    ui->amountSpinBox->setDisabled(true);
    ui->buyButton->setDisabled(true);
    ui->sellButton->setDisabled(true);
    //ui->sellAllButton->setDisabled(true);
    ui->endButton->setDisabled(true);
    ui->nameSortButton->setDisabled(true);

    // ui->currentBalanceLabel->setTextFormat(Qt::FixedNotation)

    // Initialize Ship Combo Box
    loadShipCombo();
    shipIndex = 2;  // C2 Hercules
    ui->shipComboBox->setCurrentIndex(shipIndex);
    ui->amountSpinBox->setMaximum((shipList.getCargoCap(shipIndex) - shipList.getCurrentCap(shipIndex)) * 100);

    // Connect the SQL database
    DBConnection = QSqlDatabase::addDatabase("QSQLITE");
    DBConnection.setDatabaseName(QCoreApplication::applicationDirPath() + "/SC-Log.db");

    // Validate Database connection
    qDebug() << (DBConnection.open() ? "Database Connected" : "Database not connected");

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
    routeID = -1;
    amountPurchased = 0;
    creditsEarned = 0;
    creditsSpent = 0;

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
    sort = NAME;
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
    //ui->sellAllButton->setDisabled(true);
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

void Widget::addTransaction(Cargo *item, int type) // If type == 0 item was bought. 1 means it was sold
{

    QString queryStr;
    QSqlQuery queryInsertTrans(DBConnection);
    qDebug() << 1;
    queryStr = "INSERT INTO transactions (routeID, name, quantity, price, time, sold) VALUES('"
               + QString::number(routeID) + "', '"
               + item->name + "', '"
               + QString::number(item->amount) + "', '"
               + QString::number(item->pricePerUnit) + "', '"
               + QTime::currentTime().toString() + "', '"
               + QString::number(type) + "');";
    qDebug() << 2;
    if(queryInsertTrans.prepare(queryStr))
    {
        qDebug() << 3;
        if (queryInsertTrans.exec())
        {
            qDebug() << "routeID: " << routeID;
            qDebug() << "name: " << item->name;
            qDebug() << "quantity: " << item->amount;
            qDebug() << "price: " << item->pricePerUnit;
            qDebug() << "time: : " << QTime::currentTime();
            qDebug() << "sold: : " << type;
            qDebug() << "Registed in the database";
        }
        else
        {
            qDebug() << "Failed to execute query";
        }
    }
    else
    {
        qDebug() << "Failed to prepare query";
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
    QString queryStr;
    QSqlQuery queryInsertRoute(DBConnection);
    // Ui assest formatting
    ui->endButton->setDisabled(false);

    ui->startBalDoubleSpinBox->setDisabled(true);
    ui->beginButton->setDisabled(true);
    ui->cargoNamelineEdit->setDisabled(false);
    ui->priceDoubleSpinBox->setDisabled(false);
    ui->amountSpinBox->setDisabled(false);
    ui->buyButton->setDisabled(false);
    ui->shipComboBox->setDisabled(true);
    ui->tradeHistoryButton->setDisabled(true);

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

    amountPurchased = 0;
    creditsEarned = 0;
    creditsSpent = 0;

    // start the stop watch
    timer->start(1000);
    queryStr = "INSERT INTO routes (userID, shipID, startingBalance, date, time) VALUES('"
               + QString::number(USER_ID) + "', '"
               + QString::number(shipList.getShip(shipIndex)->id) + "', '"
               + QString::number(startingBal) + "', '"
               + QDate::currentDate().toString() + "', '"
               + QTime::currentTime().toString() + "');";

    if(queryInsertRoute.prepare(queryStr))
    {
        if (queryInsertRoute.exec())
        {
            routeID = queryInsertRoute.lastInsertId().toInt();
            qDebug() << "routeID: " << routeID;
            qDebug() << "UserID: " << USER_ID;
            qDebug() << "shipID: " << shipList.getShip(shipIndex)->id;
            qDebug() << "startingBal: " << startingBal;
            qDebug() << "Date: : " << QDate::currentDate();
            qDebug() << "Time: : " << QTime::currentTime();
            qDebug() << "Registed in the database";
        }
        else
        {
            qDebug() << "Failed to execute query";
        }
    }
    else
    {
        qDebug() << "Failed to prepare query";
    }

}


void Widget::on_endButton_clicked()
{
    QString queryStr;
    QSqlQuery queryUpdateRoute(DBConnection);
    ui->beginButton->setDisabled(false);
    ui->startBalDoubleSpinBox->setDisabled(false);
    ui->beginButton->setDisabled(false);

    ui->cargoNamelineEdit->setDisabled(true);
    ui->priceDoubleSpinBox->setDisabled(true);
    ui->amountSpinBox->setDisabled(true);
    ui->buyButton->setDisabled(true);
    ui->endButton->setDisabled(true);
    ui->tradeHistoryButton->setEnabled(true);

    // stop the stop watch
    timer->stop();
    startingBal = currentBal;
    ui->startBalDoubleSpinBox->setValue(startingBal);
    //File.close();

    queryStr = "UPDATE routes SET finalBalance = '" + QString::number(currentBal) +
               "', profit = '" + QString::number(profit) +
               "', duration = '" + QString::number(hr) + ":" + QString::number(min) + ":" + QString::number(sec) +
               "' WHERE routeID = '" + QString::number(routeID) + "';";

    if(queryUpdateRoute.prepare(queryStr))
    {
        if (queryUpdateRoute.exec())
        {
            qDebug() << "finalBalance: " << currentBal;
            qDebug() << "profit: " << profit;
            qDebug() << "duration: " << QString::number(hr) + ":" + QString::number(min) + ":" + QString::number(sec);
            qDebug() << "Updated in the database";
        }
        else
        {
            qDebug() << "Failed to execute query";
        }
    }
    else
    {
        qDebug() << "Failed to prepare query";
    }

    StatScreen* statScreen = new StatScreen(this, DBConnection, routeID);
    statScreen->sendCargoPurchased(amountPurchased);
    statScreen->sendAmountRecieved(creditsEarned);
    statScreen->sendAmountSpent(creditsSpent);
    statScreen->show();
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

        amountPurchased += ceil(amount/100);
        creditsSpent += value;

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
        // if(!ui->sellAllButton->isEnabled())
        //     ui->sellAllButton->setEnabled(true);

        addTransaction(&cargoHold.back(), 0);
    }

}




/*void Widget::on_sellAllButton_clicked()
{
    sellAllDialog = new SellAllDialog(this, startingBal, currentBal);
    sellAllDialog->show();

    connect(sellAllDialog, &SellAllDialog::sendProfit, this, &Widget::profitSent);
} */



/*
void Widget::on_shipComboBox_currentIndexChanged(int index)
{
    shipIndex = index;
    emit shipChanged(index);
}
*/

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
    creditsEarned += cargoSellPtr->value;
    currentBal += cargoSellPtr->value;
    ui->editCurrentBalanceLabel->setText(QString("%1 aUEC").arg(currentBal, 0, 'f', 2));
    //reset cargo input compenents
    ui->cargoNamelineEdit->clear();
    ui->amountSpinBox->setValue(0);
    ui->priceDoubleSpinBox->setValue(0);
    ui->sellButton->setDisabled(true);

    addTransaction(cargoSellPtr, 1);
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
    if(sort == CARGO)
        return;

    ui->cargoSortButton->setDisabled(true);
    ui->nameSortButton->setEnabled(true);

    sort = CARGO;
    setDisabled(true);
    ui->shipComboBox->setDisabled(true);

    ui->shipComboBox->clear();
    shipList.sortByCargo();
    loadShipCombo();

    ui->shipComboBox->setEnabled(true);
    setEnabled(true);
}


void Widget::on_shipComboBox_activated(int index)
{
    shipIndex = index;
    emit shipChanged(index);
}


void Widget::on_nameSortButton_clicked()
{
    if(sort == NAME)
        return;

    ui->nameSortButton->setDisabled(true);
    ui->cargoSortButton->setEnabled(true);

    sort = NAME;
    setDisabled(true);
    ui->shipComboBox->setDisabled(true);

    ui->shipComboBox->clear();
    shipList.sortByName();
    loadShipCombo();

    ui->shipComboBox->setEnabled(true);
    setEnabled(true);
}


void Widget::on_tradeHistoryButton_clicked()
{
    Log* logWindow = new Log(nullptr, DBConnection, USER_ID);
    logWindow->show();
}

