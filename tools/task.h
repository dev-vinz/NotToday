#ifndef TASK_H
#define TASK_H

#include <QDateTime>
#include <QString>

#include <QList>
#include "taskstatus.h"

class Task
{
public:
    enum Recurrence
    {
        noRecurrence,
        everyDay,
        everyWeek,
        everyTwoWeek
    };

private:

    int id;
public:
    TaskStatus status;
    int priority;
    QString name;
    QDateTime deadline;
    QDateTime startTime;
    Recurrence recurrence;
    QDateTime duration;
    QList<Task*> *parent;

    void setStatus(TaskStatus status);
    void setPriority(int priority);
    void setName(QString name);
    void setDeadline(QDateTime deadline);
    void setStartTime(QDateTime startTime);
    void setRecurrence(Recurrence recurrence);
    void setDuration(QDateTime duration);

    void addParent(Task* task);
    void removeParent(Task* task);

public:

    Task(TaskStatus status, int priority, QString name, QDateTime deadline, QDateTime startTime, Recurrence recurrence = noRecurrence, QDateTime duration = QDateTime(QDate(12, 12, 12), QTime(12, 12, 12)), QList<Task*> *parent = new QList<Task*>);

    QString readTask();
    void updateTask(Task task);
    void deleteTask(Task task);
    QString getTaskStatus(TaskStatus status);
    QString getRecurrence(Recurrence recurrence);
    QString DateToString(QDateTime date);
    QString DurationToString();

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
