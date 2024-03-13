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



    // Initialize Ship Object
    selectedShip = new Ship;
    selectedShip->name = ui->shipNamelineEdit->text();
    selectedShip->cargoCap = ui->cargoCapSpinBox->value();

    runStopWatch = false;

    hr = 00;
    min = 00;
    sec = 00;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::updateTimer);
    //timer->start(1000);
}

//Deconstructor
Widget::~Widget()
{
    delete ui;
    delete timer;
    delete selectedShip;
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
    qDebug() << "selectedShip.name = " << selectedShip->name;
}

// If startBalDoubleSpinBox value is changed:
//      store current value in startingBal
void Widget::on_startBalDoubleSpinBox_valueChanged(double arg1)
{
    startingBal = ui->startBalDoubleSpinBox->value();
    currentBal = startingBal;
    ui->editCurrentBalanceLabel->setText(QString::number(currentBal) + " aUEC");
    qDebug() << "startingBal = " << startingBal;
    qDebug() << "CurrentBal = " << currentBal;
}


void Widget::on_beginButton_clicked()
{
    ui->endButton->setDisabled(false);

    ui->startBalDoubleSpinBox->setDisabled(true);
    ui->beginButton->setDisabled(true);
    ui->shipNamelineEdit->setDisabled(true);
    ui->cargoCapSpinBox->setDisabled(true);
    ui->cargoNamelineEdit->setDisabled(false);
    ui->priceDoubleSpinBox->setDisabled(false);
    ui->amountSpinBox->setDisabled(false);
    ui->buyButton->setDisabled(false);

    timer->start(1000);
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

    timer->stop();
}

