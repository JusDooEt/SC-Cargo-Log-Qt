#ifndef LOGCALENDAR_H
#define LOGCALENDAR_H

#include <QDialog>

namespace Ui {
class LogCalendar;
}

class LogCalendar : public QDialog
{
    Q_OBJECT

public:
    explicit LogCalendar(QWidget *parent = nullptr);
    ~LogCalendar();

private:
    Ui::LogCalendar *ui;

signals:
    void sendDate(QDate date);
private slots:
    void on_LogCalendar_accepted();
};

#endif // LOGCALENDAR_H
