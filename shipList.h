#ifndef SHIPLIST_H
#define SHIPLIST_H

#include <QObject>
#include <vector>
#include <QFile>

struct Ship{
    QString name;
    int     cargoCap;
    int     currentCap;
};

class ShipList : public QObject
{
    Q_OBJECT
public:
    explicit ShipList(QObject *parent = nullptr);

private:
    std::vector<Ship> list;
    int count;


signals:
};

#endif // SHIPLIST_H
