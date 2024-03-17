#ifndef SELLALLDIALOG_H
#define SELLALLDIALOG_H

#include <QDialog>

namespace Ui {
class SellAllDialog;
}

class SellAllDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SellAllDialog(QWidget *parent = nullptr);
    SellAllDialog(QWidget *parent, const double startBal , double currentBal);

    ~SellAllDialog();

private slots:
    void on_cancelButton_clicked();

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_sellAllButton_clicked();

private:
    Ui::SellAllDialog *ui;
    double             profit;
    double             currentBal;
    double             startBal;
    double             sellPrice;

signals:
    void sendProfit(const double &profit);
};

#endif // SELLALLDIALOG_H
