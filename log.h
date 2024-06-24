#ifndef LOG_H
#define LOG_H

#include <QWidget>
#include <QtSql/QtSql>
#include <QMessageBox>
#include <QListWidget>
#include "shipList.h"
#include "logcalendar.h"

namespace Ui {
class Log;
}

class Log : public QWidget
{
    Q_OBJECT

public:
    explicit Log(QWidget *parent, const QSqlDatabase DBConnection, const int USER_ID);
    ~Log();

private:
    const QSqlDatabase DBConnection;
    const int USER_ID;

    Ui::Log *ui;

    QDate date;
    QList<int> routeIDs;
    LogCalendar* calendar;

private slots:
    void onRefresh(QDate targetDate);

    //void on_calendarWidget_selectionChanged();

    //void on_routeListWidget_itemActivated(QListWidgetItem *item);

    void on_routeListWidget_itemClicked(QListWidgetItem *item);

    void on_dateButton_clicked();

signals:

};

#endif // LOG_H
