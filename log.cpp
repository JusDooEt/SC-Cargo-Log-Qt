#include "log.h"
#include "ui_log.h"

Log::Log(QWidget *parent, const QSqlDatabase DBConnection, const int USER_ID)
    : QWidget(parent)
    , ui(new Ui::Log)
    , DBConnection(DBConnection)
    , USER_ID(USER_ID)
{
    ui->setupUi(this);

    calendar = nullptr;
    date = QDate::currentDate();
    //ui->calendarWidget->selectedDate() = date;

    ui->dateButton->setText(date.toString());
    onRefresh(date);
}

Log::~Log()
{
    delete ui;
}

void Log::onRefresh(QDate targetDate)
{
    QSqlQuery queryFindRoute;
    QString queryStr;
    QString listWidgetStr;
    routeIDs.clear();

    ui->routeListWidget->clear();
    ui->routeDetailsTextEdit->clear();

    ui->dateButton->setText(targetDate.toString());

    queryStr = "SELECT * FROM routes WHERE userID='" + QString::number(USER_ID) +
               "' AND date = '" + targetDate.toString() + "';";

    if(queryFindRoute.prepare(queryStr))
    {
        if (queryFindRoute.exec())
        {
            while (queryFindRoute.next())
            {
                routeIDs.append(queryFindRoute.value("routeID").toInt());
                listWidgetStr = queryFindRoute.value("time").toString() + '\n' +
                                "Duration: " + queryFindRoute.value("duration").toString() + '\n' +
                                //"Ship: " + ShipList::getName(queryFindRoute.value("shipID").toInt()) + '\n' +
                                "Starting Balance: " + QString("%1 aUEC").arg(queryFindRoute.value("startingBalance").toDouble(), 0, 'f', 2) + '\n' +
                                "Final Balance: " + QString("%1 aUEC").arg(queryFindRoute.value("finalBalance").toDouble(), 0, 'f', 2) + '\n' +
                                "Profit: " + QString("%1 aUEC").arg(queryFindRoute.value("profit").toDouble(), 0, 'f', 2) + '\n';

                ui->routeListWidget->addItem(listWidgetStr);
            }
        }
        else
        {
            qDebug() << "<ERROR> - " << QSqlError().text();
        }
    }
    else
    {
        qDebug() << "<ERROR> - " << QSqlError().text();
    }
}


/*void Log::on_calendarWidget_selectionChanged()
{
    //date = ui->calendarWidget->selectedDate();
    onRefresh(date);
} */

/*
void Log::on_routeListWidget_itemActivated(QListWidgetItem *item)
{
    int i = ui->routeListWidget->currentRow();
    int routeID = routeIDs[i];
    QSqlQuery queryFindTrans;
    QString queryStr;
    QString textEditStr;
    routeIDs.clear();

    ui->routeListWidget->clear();
    ui->routeDetailsTextEdit->clear();

    queryStr = "SELECT * FROM transactions WHERE routeID='" + QString::number(routeID) + "';";

    if(queryFindTrans.prepare(queryStr))
    {
        if (queryFindTrans.exec())
        {
            while (queryFindTrans.next())
            {
                textEditStr = queryFindTrans.value("time").toString() + '\n' +
                            "Item name: " + queryFindTrans.value("name").toString() + '\n' +
                            "Price Per Unit: " + queryFindTrans.value("price").toString() + '\n' +
                            "Quantity: " + queryFindTrans.value("quantity").toString() + '\n' +
                            (queryFindTrans.value("sold").toInt() ? "Purchased" : "Sold") + '\n';
                ui->routeDetailsTextEdit->append(textEditStr);
            }
        }
        else
        {
            qDebug() << "<ERROR> - " << QSqlError().text();
        }
    }
    else
    {
        qDebug() << "<ERROR> - " << QSqlError().text();
    }
} */


void Log::on_routeListWidget_itemClicked(QListWidgetItem *item)
{
    int i = ui->routeListWidget->currentRow();
    int routeID = routeIDs[i];

    ui->routeDetailsTextEdit->clear();
    QSqlQuery queryFindTrans;
    QString queryStr;
    QString textEditStr;

    queryStr = "SELECT * FROM transactions WHERE routeID='" + QString::number(routeID) + "';";

    if(queryFindTrans.prepare(queryStr))
    {
        if (queryFindTrans.exec())
        {
            while (queryFindTrans.next())
            {
                textEditStr = queryFindTrans.value("time").toString() + '\n' +
                              "Item: " + queryFindTrans.value("name").toString() + '\n' +
                              "Price Per Unit: " + QString("%1 aUEC").arg(queryFindTrans.value("price").toDouble(), 0, 'f', 2) + '\n' +
                              "Quantity: " + queryFindTrans.value("quantity").toString() + " UNITS" + '\n' +
                              (!queryFindTrans.value("sold").toInt() ? "PURCHASED" : "SOLD") + '\n';
                ui->routeDetailsTextEdit->append(textEditStr);
            }
        }
        else
        {
            qDebug() << "<ERROR> - " << QSqlError().text();
        }
    }
    else
    {
        qDebug() << "<ERROR> - " << QSqlError().text();
    }
}


void Log::on_dateButton_clicked()
{
    calendar = new LogCalendar(this);
    calendar->show();
    connect(calendar, &LogCalendar::sendDate, this, &Log::onRefresh);
}

