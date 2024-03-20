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

std::vector<Ship> ShipList::getList() const
{
    return list;
}

int ShipList::getShipCount() const
{
    return count;
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
