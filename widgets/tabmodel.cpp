#include "tabmodel.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                           CONSTRUCTORS                            *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

TabModel::TabModel(QWidget *_parent) : QTabBar(_parent)
{
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                         PROTECTED METHODS                         *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

Task TabModel::createTask()
{
    TaskStatus status = TaskStatus::DOING;

    // TODO
    int prio = 34;

    QString name = "Tester le CRUD";
    QDateTime deadline = QDateTime(QDate(2024, 12, 2), QTime(0, 0, 0));
    QDateTime start = QDateTime(QDate(2023, 12, 2), QTime(0, 0, 0));
    Recurrence recu = Recurrence::EVERY_TWO_WEEKS;
    QDateTime dura = QDateTime(QDate(0, 0, 0), QTime(15, 15, 15));

    return Task(status ,prio, name, deadline, start, recu, dura);
}
