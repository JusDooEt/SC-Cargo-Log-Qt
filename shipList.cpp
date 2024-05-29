#include <QtSql/QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include "shipList.h"
#include "qsqlquery.h"
#include "qcoreapplication.h"
#include <QDebug>

ShipList::ShipList(QObject *parent) : QObject{parent}
{
    count = 0;
    inFile = "shipsFile.txt";
    CreateList();
}

ShipList::~ShipList()
{
    list.clear();
}

void ShipList::setMake(int index, QString make)
{
    if(index >= count)
        return;
    list[index]->make = make;
}

void ShipList::setModel(int index, QString model)
{
    if(index >= count)
        return;
    list[index]->model = model;
}

void ShipList::setCargoCap(int index, int cargoCap)
{
    if(index >= count)
        return;
    list[index]->cargoCap = cargoCap;
}

void ShipList::setCurrentCap(int index, int currentCap)
{
    if(index >= count)
        return;
    list[index]->currentCap = currentCap;
}

void ShipList::setType(int index, ShipType type)
{
    if(index >= count)
        return;
    list[index]->type = type;
}

void ShipList::sortByCargo()
{
    quickSort(list, 0, list.size() - 1, CARGO);

}

void ShipList::sortByName()
{
    quickSort(list, 0, list.size() - 1, NAME);

}


std::vector<Ship*> ShipList::getList() const
{
    return list;
}

int ShipList::getShipCount() const
{
    return count;
}

QString ShipList::getName(int index) const
{
    if(index >= count)
        return NULL;
    return list[index]->make + ", " + list[index]->model;
}

QString ShipList::getMake(int index) const
{
    if(index >= count)
        return NULL;

    return list[index]->make;
}

QString ShipList::getModel(int index) const
{
    if(index >= count)
        return NULL;

    return list[index]->model;
}

int ShipList::getCargoCap(int index) const
{
    if(index >= count)
        return -1;

    return list[index]->cargoCap;
}

int ShipList::getCurrentCap(int index) const
{
    if(index >= count)
        return -1;

    return list[index]->currentCap;
}

ShipType ShipList::getType(int index) const
{
    if(index >= count)
        return ERROR;

    return list[index]->type;
}

Ship* ShipList::getShip(int index) const
{
    if(index >= count)
        return nullptr;

    return list[index];
}

void ShipList::CreateList()
{
    int         id;
    QString     make;
    QString     model;
    int         shipInv;
    ShipType    type;
    Ship*       shipPtr;
    QSqlDatabase DBConnection;

    // Connect the SQL database
    DBConnection = QSqlDatabase::addDatabase("QSQLITE");
    DBConnection.setDatabaseName(QCoreApplication::applicationDirPath() + "/SC-Log.db");

    QSqlQuery queryFindShip(DBConnection);
    QString query = "SELECT * FROM ships;";

    // Validate Database connection
    qDebug() << (DBConnection.open() ? "Database Connected" : "Database not connected") << " - From shipList.cpp";

    if(!queryFindShip.prepare(query))
    {
        qDebug() << "<ERROR> - " << QSqlError().text();
    }
    else
    {
        if(!queryFindShip.exec())
        {
            qDebug() << "<ERROR> - " << QSqlError().text();
        }
        else
        {
            count = 0;
            while(queryFindShip.next())
            {
                id = queryFindShip.value("shipID").toInt();
                make = queryFindShip.value("make").toString();
                model = queryFindShip.value("model").toString();
                shipInv = queryFindShip.value("capacity").toInt();

                // Create a new ship object with input variables
                shipPtr = new Ship(id,
                                   make,
                                   model,
                                   shipInv,
                                   setShipType(queryFindShip.value("class").toString()));
                list.push_back(shipPtr);
                count++;
                shipPtr = nullptr;

                // Debug output in console
                qDebug() << "list[" << count - 1 << "]";
                qDebug() << "Make: " << list[count - 1]->make;
                qDebug() << "Model: " << list[count - 1]->model;
                qDebug() << "Cargo Cap: " << list[count - 1]->cargoCap;
                switch (list[count-1]->type) {
                case SMALL:
                    qDebug() << "Type: SMALL";
                    break;
                case MEDIUM:
                    qDebug() << "Type: MEDIUM";
                    break;
                case LARGE:
                    qDebug() << "Type: Large";
                    break;
                default:
                    qDebug() << "Type: ERROR";
                    break;
                }
                qDebug() << "-------------------------";
            }
        }
    }


    DBConnection.close();
    qDebug() << "Finished Loading Ships. Database closed";
    /*QFile File(inFile);
    if(!File.exists())
    {
        qDebug() << "File doesnt exist";
    }
    if (!File.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "open error" << File.OpenError;
        return;
    }

    QTextStream stream(&File);
    while (!stream.atEnd())
    {
        // Read In Data from File into Variables
        qDebug() << "reading file...";
        make = stream.readLine();
        model = stream.readLine();
        shipInv = stream.readLine().toInt();
        QString typeStr = stream.readLine();

        // Create a new ship object with input variables
        shipPtr = new Ship(make, model, shipInv, setShipType(typeStr));
        list.push_back(shipPtr);
        count++;
        shipPtr = nullptr;

        // Debug output in console
        qDebug() << "list[" << count - 1 << "]";
        qDebug() << "Make: " << list[count - 1]->make;
        qDebug() << "Model: " << list[count - 1]->model;
        qDebug() << "Cargo Cap: " << list[count - 1]->cargoCap;
        switch (list[count-1]->type) {
        case SMALL:
            qDebug() << "Type: SMALL";
            break;
        case MEDIUM:
            qDebug() << "Type: MEDIUM";
            break;
        case LARGE:
            qDebug() << "Type: Large";
            break;
        default:
            qDebug() << "Type: ERROR";
            break;
        }
        qDebug() << "-------------------------";

    }
    File.close();
    qDebug() << "Finished Reading File";*/

}

ShipType ShipList::setShipType(QString typeStr)
{
    if (typeStr == "S")
    {
        return SMALL;
    }
    else if (typeStr == "M")
    {
        return MEDIUM;
    }
    else if (typeStr == "L")
    {
        return LARGE;
    }
    else
    {
        qDebug() << "error setting type";
        return ERROR;
    }
}

void ShipList::swap(Ship*& a, Ship*& b)
{
    //cout << "<swapping " << a << " & " << b << ">\n";
    Ship* temp;
    temp = a;
    a = b;
    b = temp;
    //cout << "<Finished>\n";
}

int ShipList::partitionCargo(std::vector<Ship*>& arr, int low, int high)
{
    int pivot = arr[high]->cargoCap;
    int i = low - 1;

    for (int j = low; j <= high; j++)
    {
        if (arr[j]->cargoCap < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

int ShipList::partitionString(std::vector<Ship*>& arr, int low, int high)
{
    QString pivot = arr[high]->name;
    int i = low - 1;

    for (int j = low; j <= high; j++)
    {
        if (arr[j]->name < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void ShipList::quickSort(std::vector<Ship*>& arr, int low, int high, SortType mode)
{
    if (low < high)
    {
        int pivot = mode == CARGO ? partitionCargo(arr, low, high) : partitionString(arr, low, high);

        quickSort(arr, low, pivot - 1, mode);
        quickSort(arr, pivot + 1, high, mode);
    }
}


void ShipList::printArray(std::vector<Ship*> A, int size)
{
    for (auto i = 0; i < size; i++)
        qDebug() << A[i]->make << " " << A[i]->model;
}
