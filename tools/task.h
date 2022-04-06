#ifndef TASK_H
#define TASK_H

#include <QDateTime>
#include <QString>

#include "taskstatus.h"

class Task
{
private:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                            ATTRIBUTES                             *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    int id;
    TaskStatus status;
    int priority;
    QString name;
    QDateTime deadline;
    QDateTime startTime;
    QDateTime recurrence;
    QDateTime duration;
    Task **parent;

public:
    Task();

    /* * * * * * * * * * * * * * * * * * *\
    |*              GETTERS              *|
    \* * * * * * * * * * * * * * * * * * */

    int getId() const;
    int getPriority() const;
    QString getName() const;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PUBLIC METHODS                           *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    bool isCheckable() const;
};

#endif // TASK_H
