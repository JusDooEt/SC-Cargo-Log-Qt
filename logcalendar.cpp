#include "logcalendar.h"
#include "ui_logcalendar.h"

LogCalendar::LogCalendar(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LogCalendar)
{
    ui->setupUi(this);
}

LogCalendar::~LogCalendar()
{
    delete ui;
}

void LogCalendar::on_LogCalendar_accepted()
{
    emit sendDate(ui->calendarWidget->selectedDate());
}

