#include "widget.h"
#include "./ui_widget.h"


//Constructor
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Set up load up state
    ui->shipNamelineEdit->setText("Crusader, C2 Hercules Starlifter");
    ui->cargoCapSpinBox->setValue(696);
    ui->cargoNamelineEdit->setDisabled(true);
    ui->priceDoubleSpinBox->setDisabled(true);
    ui->amountSpinBox->setDisabled(true);
    ui->buyButton->setDisabled(true);
    ui->sellButton->setDisabled(true);
    ui->sellAllButton->setDisabled(true);
    ui->endButton->setDisabled(true);
    // ui->currentBalanceLabel->setTextFormat(Qt::FixedNotation)


    // Initialize Ship Object
    selectedShip = new Ship;
    selectedShip->name = ui->shipNamelineEdit->text();
    selectedShip->cargoCap = ui->cargoCapSpinBox->value();
    selectedShip->currentCap = 0;

    runStopWatch = false;
    sellAll      = false;
    totalValue = 0;

    hr = 00;
    min = 00;
    sec = 00;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::updateTimer);
    //timer->start(1000);

    cargoHead = nullptr;

    //For testing purposes

    startingBal = 10000000;
    currentBal  = startingBal;
    ui->startBalDoubleSpinBox->setValue(startingBal);
    ui->editCurrentBalanceLabel->setText(QString("%1 aUEC").arg(currentBal, 0, 'f', 2));
}

//Deconstructor
Widget::~Widget()
{
    delete ui;
    delete timer;
    delete selectedShip;
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


// When return is pressed in shipNameLineEdit:
//      store the current text in selectedShip.name
void Widget::on_shipNamelineEdit_returnPressed()
{
    selectedShip->name = ui->shipNamelineEdit->text();
    //qDebug() << "selectedShip.name = " << selectedShip->name;
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
    ui->shipNamelineEdit->setDisabled(true);
    ui->cargoCapSpinBox->setDisabled(true);
    ui->cargoNamelineEdit->setDisabled(false);
    ui->priceDoubleSpinBox->setDisabled(false);
    ui->amountSpinBox->setDisabled(false);
    ui->buyButton->setDisabled(false);

    // reset clock values;
    hr = 0;
    min = 0;
    sec = 0;


    // start the stop watch
    timer->start(1000);

    selectedShip->name = ui->shipNamelineEdit->text();
    selectedShip->cargoCap = ui->cargoCapSpinBox->value();
    selectedShip->currentCap = 0;
    ui->editCapcityNumLabel->setText(QString::number(selectedShip->currentCap) + " / " + QString::number(selectedShip->cargoCap) + " SCU");
}


void Widget::on_endButton_clicked()
{
    ui->beginButton->setDisabled(false);
    ui->startBalDoubleSpinBox->setDisabled(false);
    ui->beginButton->setDisabled(false);
    ui->shipNamelineEdit->setDisabled(false);
    ui->cargoCapSpinBox->setDisabled(false);

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

        valid = (ceil(ptr->amount/100) <= (selectedShip->cargoCap - selectedShip->currentCap) &&
                 ptr->value  <= currentBal);

        if(!valid)
        {
            cargoBuyError = new QDialog(this);

            cargoBuyError->setWindowModality(Qt::WindowModality::ApplicationModal);
            cargoBuyError->setMinimumSize(400,100);


            QLabel* errorMsgLabel = new QLabel(cargoBuyError);
            errorMsgLabel->setText("Error with purchase. (Please check cargo hold and current balance)");
            errorMsgLabel->setAlignment(Qt::AlignCenter);
            errorMsgLabel->setGeometry(0,20,400,20);
            errorMsgLabel->show();

            QPushButton* okButton = new QPushButton(cargoBuyError);
            connect(okButton, &QPushButton::clicked, this, &Widget::on_okButton_clicked);
            okButton->setText("OK");
            okButton->setGeometry(175,50, 50,25);
            okButton->show();

            cargoBuyError->show();
            return;
        }

        ptr->next = cargoHead;
        cargoHead = ptr;

        currentBal -= cargoHead->value;
        totalValue += cargoHead->value;
        selectedShip->currentCap += cargoHead->amount / 100;

        ui->editCurrentBalanceLabel->setText(QString("%1 aUEC").arg(currentBal, 0, 'f', 2));
        ui->editValueLabel->setText(QString("%1 aUEC").arg(totalValue, 0, 'f', 2));
        ui->editCapcityNumLabel->setText(QString::number(selectedShip->currentCap) + " / " + QString::number(selectedShip->cargoCap) + " SCU");
        cargoDesc = (cargoHead->name +
                    "\nAmount: " + QString::number(cargoHead->amount) +
                    "\nPrice per UNIT: " + QString::number(cargoHead->pricePerUnit) + " aUEC"
                    "\nValue: " + QString("%1 aUEC").arg(cargoHead->value, 0, 'f', 2) +
                    "\n\n--------------------------------------------------\n\n");
        ui->cargoHoldTextEdit->append(cargoDesc);

        // if(!ui->sellButton->isEnabled())
        //     ui->sellButton->setEnabled(true);
        if(!ui->sellAllButton->isEnabled())
            ui->sellAllButton->setEnabled(true);
    }

}

void Widget::on_okButton_clicked()
{
    cargoBuyError->close();
}





void Widget::on_sellAllButton_clicked()
{
    //sellAll = false;
    sellAllDialog = new QDialog(this);
    sellAllDialog->setWindowModality(Qt::WindowModality::ApplicationModal);
    sellAllDialog->setMinimumSize(400,100);

    QLabel* sellAllDialogLabel = new QLabel(sellAllDialog);
    sellAllDialogLabel->setText("Do you want to sell all your cargo and end your run?");
    sellAllDialogLabel->show();

    QPushButton* yesButton = new QPushButton(sellAllDialog);
    connect(yesButton, &QPushButton::clicked, this, &Widget::on_okButton_clicked);
    yesButton->setText("Yes");
    yesButton->setGeometry(175,50, 50,25);
    yesButton->show();

    QPushButton* noButton = new QPushButton(sellAllDialog);
    connect(noButton, &QPushButton::clicked, this, [=](){
        if(sellAllDialog->isEnabled())
            sellAllDialog->close();
    });
    noButton->setText("Yes");
    noButton->setGeometry(175,50, 50,25);
    noButton->show();
}

void Widget::on_yesDialongButton_clicked()
{
    sellAllPriceDialog = new QDialog(this);
    sellAllPriceDialog->setWindowModality(Qt::WindowModality::ApplicationModal);
    sellAllPriceDialog->setMinimumSize(600,100);

    QLabel* sellAllPriceLabel = new QLabel(sellAllPriceDialog);
    sellAllPriceLabel->setText("Sell All Value: ");
    sellAllPriceLabel->show();

    QDoubleSpinBox* sellAllDoubleSpinBox = new QDoubleSpinBox(sellAllPriceDialog);
    sellAllDoubleSpinBox->setValue(0.00);
    sellAllDoubleSpinBox->show();

    QLabel* auecLabel = new QLabel(sellAllPriceDialog);
    auecLabel->setText(" auec");
    auecLabel->show();

    QHBoxLayout* priceFormat = new QHBoxLayout(sellAllPriceDialog);
    priceFormat->addWidget(sellAllPriceLabel);
    priceFormat->addWidget(sellAllDoubleSpinBox);
    priceFormat->addWidget(auecLabel);
    priceFormat->setEnabled(true);

    QPushButton* confirmButton = new QPushButton(sellAllPriceDialog);
    connect(confirmButton, &QPushButton::clicked, this, [=](){
        if(sellAllDoubleSpinBox->value() > totalValue)
        {
           sellAllPrice = sellAllDoubleSpinBox->value();
        }

        ui->buyButton->setDisabled(true);
        ui->sellAllButton->setDisabled(true);
        ui->sellButton->setDisabled(true);
        profit = sellAllPrice - totalValue;
        ui->editProfitLabel->setText(QString("%1 aUEC").arg(profit, 0, 'f', 2));
        selectedShip->currentCap = 0;
        ui->editCapcityNumLabel->setText(QString::number(selectedShip->currentCap) + " / " + QString::number(selectedShip->cargoCap)
                                         + " SCU");
        ui->cargoHoldTextEdit->clear();
        totalValue = 0;
        ui->editValueLabel->setText(QString("%1 aUEC").arg(totalValue, 0, 'f', 2));
        currentBal += sellAllPrice;
        ui->editCurrentBalanceLabel->setText(QString("%1 aUEC").arg(currentBal, 0, 'f', 2));
        startingBal = currentBal;
        ui->startBalDoubleSpinBox->setValue(startingBal);

        sellAllPriceDialog->close();
        sellAllDialog->close();
    });
    confirmButton->setText("Confirm");
    confirmButton->setGeometry(175,50, 50,25);
    confirmButton->show();

    QPushButton* cancelButton = new QPushButton(sellAllPriceDialog);
    connect(cancelButton, &QPushButton::clicked, this, [=](){
        sellAllPriceDialog->close();
        sellAllDialog->close();
    });
    cancelButton->setText("Cancel");
    cancelButton->setGeometry(175,50, 50,25);
    cancelButton->show();

    QHBoxLayout* dialogButtons = new QHBoxLayout(sellAllPriceDialog);
    dialogButtons->addWidget(confirmButton);
    dialogButtons->addWidget(cancelButton);
    dialogButtons->setEnabled(true);

    QVBoxLayout* sellAllPriceLayout = new QVBoxLayout(sellAllPriceDialog);
    sellAllPriceLayout->addItem(priceFormat);
    sellAllPriceLayout->addItem(dialogButtons);
    sellAllPriceLayout->setEnabled(true);
}


void Widget::on_cargoCapSpinBox_valueChanged(int arg1)
{
    selectedShip->cargoCap = arg1;
}

