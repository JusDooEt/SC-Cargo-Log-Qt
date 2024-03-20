#include "shipList.h"
#include <QDebug>
#include <fstream>
#include <iostream>
#include <string>

ShipList::ShipList(QObject *parent) : QObject{parent}
{
    count = 0;
    inFile = "shipsFile.txt";
    CreateList();
}

void ShipList::CreateList()
{
    QString     make;
    QString     model;
    int         shipInv;
    ShipType    type;

    // std::ifstream   fin;
    // std::string     typeStr;

    // fin.open("shipsFile.txt");
    // while(fin)
    // {
    //     qDebug() << "reading file...";
    //     getline(fin,makeStr);
    //     getline(fin, modelStr);
    //     fin >> shipInv;
    //     fin.ignore();
    //     getline(fin, typeStr);
    //     fin.ignore();
    //     list.push_back(Ship(QString::fromStdString(makeStr), QString::fromStdString(modelStr), shipInv, setShipType(QString::fromStdString(typeStr))));
    //     count++;

    //     // Debug output in console
    //     qDebug() << "list[" << count - 1 << "]";
    //     qDebug() << "Make: " << list[count - 1].make;
    //     qDebug() << "Model: " << list[count - 1].model;
    //     qDebug() << "Cargo Cap: " << list[count - 1].cargoCap;
    //     switch (list[count-1].type) {
    //     case SMALL:
    //         qDebug() << "Type: SMALL";
    //         break;
    //     case MEDIUM:
    //         qDebug() << "Type: MEDIUM";
    //         break;
    //     case LARGE:
    //         qDebug() << "Type: Large";
    //         break;
    //     default:
    //         qDebug() << "Type: ERROR";
    //         break;
    //     }
    //     qDebug() << "-------------------------";
    // }

    QFile File("shipsFile.txt");
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
        //in.readLine();
        list.push_back(Ship(make, model, shipInv, setShipType(typeStr)));
        count++;

        // Debug output in console
        qDebug() << make; // "list[" << count - 1 << "]";
        qDebug() << model; //"Make: " << list[count - 1].make;
        qDebug() << shipInv; //"Model: " << list[count - 1].model;
        qDebug() << typeStr;
        //qDebug() << "Cargo Cap: " << list[count - 1].cargoCap;
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
