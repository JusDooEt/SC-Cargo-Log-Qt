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

void ShipList::sortByCargo()
{
    mergeSort(list, 0, list.size() - 1);
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


void ShipList::merge(std::vector<Ship>& array, int const left,
           int const mid, int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    // Create temp arrays
    auto *leftArray = new std::vector<Ship> (subArrayOne),
        *rightArray = new std::vector<Ship> (subArrayTwo);

    // Copy data to temp arrays leftArray[]
    // and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        (*leftArray)[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        (*rightArray)[j] = array[mid + 1 + j];

    // Initial index of first sub-array
    // Initial index of second sub-array
    auto indexOfSubArrayOne = 0,
        indexOfSubArrayTwo = 0;

    // Initial index of merged array
    int indexOfMergedArray = left;

    // Merge the temp arrays back into
    // array[left..right]
    while (indexOfSubArrayOne < subArrayOne &&
           indexOfSubArrayTwo < subArrayTwo)
    {
        if ((*leftArray)[indexOfSubArrayOne].cargoCap <=
            (*rightArray)[indexOfSubArrayTwo].cargoCap)
        {
            array[indexOfMergedArray] =
                (*leftArray)[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else
        {
            array[indexOfMergedArray] =
                (*rightArray)[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne)
    {
        array[indexOfMergedArray] =
            (*leftArray)[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo)
    {
        array[indexOfMergedArray] =
            (*rightArray)[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }

    delete rightArray;
    delete leftArray;
    printArray(array, array.size());
}


void ShipList::mergeSort(std::vector<Ship> array,
               int const begin,
               int const end)
{
    // Returns recursively
    if (begin >= end)
        return;

    auto mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}


void ShipList::printArray(std::vector<Ship> A, int size)
{
    for (auto i = 0; i < size; i++)
        qDebug() << A[i].make << " " << A[i].model;
}
