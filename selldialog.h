#ifndef SELLDIALOG_H
#define SELLDIALOG_H

#include <QDialog>

struct Cargo{
    Cargo(QString name, double pricePerUnit, double value, int amount)
    {
        this->name = name;
        this->pricePerUnit = pricePerUnit;
        this->value = value;
        this->amount = amount;
        sold = false;
    }
    QString name;
    double  pricePerUnit;
    double  value;
    int     amount;
    bool    sold;
};

namespace Ui {
class SellDialog;
}

class SellDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SellDialog(QWidget *parent = nullptr);
    SellDialog(QWidget *parent, Cargo currentCargo, Cargo cargoSold);
    ~SellDialog();

private:
    Ui::SellDialog *ui;
    Cargo* cargoSoldPtr;
    Cargo* currentCargoPtr;

signals:
    void sell();
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // SELLDIALOG_H
