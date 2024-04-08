#ifndef SHIPLIST_H
#define SHIPLIST_H

#include <QObject>
#include <QTextStream>
#include <QDir>
#include <vector>
#include <QFile>
#include <iostream>

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
    Ship()
    {
        this->make = "";
        this->model = "";
        this->cargoCap = 0;
        this->type = ERROR;
        this->currentCap = 0;
    }
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
    //Constructor + Desctructor
    explicit ShipList(QObject *parent = nullptr);
    ~ShipList();

    //Mutators
    void setMake(int index, QString make);
    void setModel(int index, QString model);
    void setCargoCap(int index, int cargoCap);
    void setCurrentCap(int index, int currentCap);
    void setType(int index, ShipType type);
    void sortByCargo();

    //Accessors
    std::vector<Ship> getList() const;
    int getShipCount() const;
    QString getName(int index) const;
    QString getMake(int index) const;
    QString getModel(int index) const;
    int getCargoCap(int index)const;
    int getCurrentCap(int index) const;
    ShipType getType(int index) const;
    Ship getShip(int index) const;

private:
    std::vector<Ship> list;
    int count;
    QString inFile;

    void CreateList();
    ShipType setShipType(QString typeStr);
    void merge(std::vector<Ship>& array, int const left,
                      int const mid, int const right);
    void mergeSort(std::vector<Ship> array,
                          int const begin,
                          int const end);


    void printArray(std::vector<Ship> A, int size);
signals:
};

#endif // SHIPLIST_H
