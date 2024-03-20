#ifndef SHIPLIST_H
#define SHIPLIST_H

#include <QObject>
#include <QTextStream>
#include <QDir>
#include <vector>
#include <QFile>

enum ShipType
{
    //Type of ship depending on cargo space
    SMALL,
    MEDIUM,
    LARGE,
    ERROR
};

struct Ship{
    //Overloaded Constructor
    Ship(QString make, QString model, int cargoCap, ShipType type)
    {
        this->make = make;
        this->model = model;
        this->cargoCap = cargoCap;
        this->type = type;
        currentCap = 0;
    }

    //Ship Variables
    QString     make;
    QString     model;
    int         cargoCap;
    int         currentCap;
    ShipType    type;
};

class ShipList : public QObject
{
    Q_OBJECT
public:
    explicit ShipList(QObject *parent = nullptr);

private:
    std::vector<Ship> list;
    int count;
    QString inFile;

    void CreateList();
    ShipType setShipType(QString typeStr);


signals:
};

#endif // SHIPLIST_H
