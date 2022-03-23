#ifndef TASK_H
#define TASK_H

#include <QDateTime>
#include <QString>

#include "taskstatus.h"

class Task
{
private:
    TaskStatus status;
    int priority;
    QString name;
    QDateTime deadline;
    QDateTime startTime;
    QDateTime recurrence;
    QDateTime duration;
    Task *parent;

public:
    Task();

    bool isCheckable() const;
};

#endif // TASK_H
