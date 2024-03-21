#include "shipList.h"
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
    list[index].make = make;
}

void ShipList::setModel(int index, QString model)
{
    if(index >= count)
        return;
    list[index].model = model;
}

void ShipList::setCargoCap(int index, int cargoCap)
{
    if(index >= count)
        return;
    list[index].cargoCap = cargoCap;
}

void ShipList::setCurrentCap(int index, int currentCap)
{
    if(index >= count)
        return;
    list[index].currentCap = currentCap;
}

void ShipList::setType(int index, ShipType type)
{
    if(index >= count)
        return;
    list[index].type = type;
}


std::vector<Ship> ShipList::getList() const
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
    return list[index].make + ", " + list[index].model;
}

QString ShipList::getMake(int index) const
{
    if(index >= count)
        return NULL;

    return list[index].make;
}

QString ShipList::getModel(int index) const
{
    if(index >= count)
        return NULL;

    return list[index].model;
}

int ShipList::getCargoCap(int index) const
{
    if(index >= count)
        return -1;

    return list[index].cargoCap;
}

int ShipList::getCurrentCap(int index) const
{
    if(index >= count)
        return -1;

    return list[index].currentCap;
}

ShipType ShipList::getType(int index) const
{
    if(index >= count)
        return ERROR;

    return list[index].type;
}

Ship ShipList::getShip(int index) const
{
    if(index >= count)
        return Ship("", "", 0, ERROR);

    return list[index];
}

void ShipList::CreateList()
{
    QString     make;
    QString     model;
    int         shipInv;
    ShipType    type;

    QFile File(inFile);
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
        qDebug() << "reading file...";
        make = stream.readLine();
        model = stream.readLine();
        shipInv = stream.readLine().toInt();
        QString typeStr = stream.readLine();
        list.push_back(Ship(make, model, shipInv, setShipType(typeStr)));
        count++;

        // Debug output in console
        qDebug() << "list[" << count - 1 << "]";
        qDebug() << "Make: " << list[count - 1].make;
        qDebug() << "Model: " << list[count - 1].model;
        qDebug() << "Cargo Cap: " << list[count - 1].cargoCap;
        switch (list[count-1].type) {
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
    qDebug() << "Finished Reading File";
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
