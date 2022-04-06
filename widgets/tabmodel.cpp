#include "tabmodel.h"

TabModel::TabModel(QWidget *_parent) : QTabBar(_parent)
{
}

Task TabModel::createTask()
{
    TaskStatus status = TaskStatus::DOING;
    int prio = 34;
    QString name = "Tester le CRUD";
    QDateTime deadline =QDateTime(QDate(2024,12,2), QTime(0,0,0));
    QDateTime start =QDateTime(QDate(2023,12,2), QTime(0,0,0));
    Task::Recurrence recu = Task::Recurrence::everyTwoWeek;
    QDateTime dura = QDateTime(QDate(0,0,0), QTime(15,15,15));
    return Task(status,prio, name, deadline,start,recu,dura);
}
