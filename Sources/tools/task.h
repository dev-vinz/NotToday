#ifndef TASK_H
#define TASK_H

#include <QDateTime>
#include <QList>
#include <QString>
#include <QList>

#include "recurrence.h"
#include "taskstatus.h"
#include "utils.h"

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
    Recurrence recurrence;
    QDateTime duration;
    QList<Task *> parent;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PRIVATE METHODS                          *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

public:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                           CONSTRUCTORS                            *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    Task(TaskStatus status, int priority, QString name, QDateTime deadline, QDateTime startTime, Recurrence recurrence = Recurrence::NO_RECURRENCE, QDateTime duration = QDateTime(QDate(12, 12, 12), QTime(12, 12, 12)), QList<Task *> parent = QList<Task *>());
    ~Task();

    /* * * * * * * * * * * * * * * * * * *\
    |*              GETTERS              *|
    \* * * * * * * * * * * * * * * * * * */

    int getId() const;
    int getPriority() const;

    QDateTime getDeadline() const;
    QDateTime getDuration() const;
    QDateTime getStartTime() const;

    QList<Task *> getParents() const;

    QString getDurationString() const;
    QString getName() const;
    QString getRecurrenceString() const;
    QString getStatusString() const;

    Recurrence getRecurrence() const;

    TaskStatus getStatus() const;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PUBLIC METHODS                           *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    bool isCheckable() const;

    void addParent(Task* task);
    void deleteTask(Task task);
    void removeParent(Task* task);
    void updateTask(Task task);

    QString readTask() const;
};

#endif // TASK_H
