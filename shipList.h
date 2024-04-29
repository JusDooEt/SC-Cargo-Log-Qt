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

enum SortType
{
    CARGO,
    NAME,
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
        this->name = "";
    }
    Ship(QString make, QString model, int cargoCap, ShipType type)
    {
        this->make = make;
        this->model = model;
        this->cargoCap = cargoCap;
        this->type = type;
        currentCap = 0;
        this->name = make + ", " + model;
    }

    //Ship Variables
    QString     make;
    QString     model;
    int         cargoCap;
    int         currentCap;
    ShipType    type;
    QString     name;


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
    void sortByName();

    //Accessors
    std::vector<Ship*> getList() const;
    int getShipCount() const;
    QString getName(int index) const;
    QString getMake(int index) const;
    QString getModel(int index) const;
    int getCargoCap(int index)const;
    int getCurrentCap(int index) const;
    ShipType getType(int index) const;
    Ship* getShip(int index) const;
    void printArray(std::vector<Ship*> A, int size);

    void swap(Ship*& a, Ship*& b);
    int partitionCargo(std::vector<Ship*>& arr, int low, int high);
    int partitionString(std::vector<Ship*>& arr, int low, int high);
    void quickSort(std::vector<Ship*>& arr, int low, int high, SortType mode);

private:
    std::vector<Ship*> list;
    int count;
    QString inFile;

    void CreateList();
    ShipType setShipType(QString typeStr);



signals:
};

#endif // SHIPLIST_H
