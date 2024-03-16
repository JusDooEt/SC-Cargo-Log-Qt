#ifndef BUYERRORDIALOG_H
#define BUYERRORDIALOG_H

#include <QDialog>

namespace Ui {
class BuyErrorDialog;
}

class BuyErrorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuyErrorDialog(QWidget *parent = nullptr);
    ~BuyErrorDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::BuyErrorDialog *ui;
};

#endif // BUYERRORDIALOG_H
