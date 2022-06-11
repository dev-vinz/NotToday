#ifndef TASK_H
#define TASK_H

#include <QDateTime>
#include <QList>
#include <QString>
#include <QList>

#include "recurrence.h"
#include "taskstatus.h"
#include "timespan.h"
#include "utils.h"

class Utils;

class Task
{

private:
    static int CURRENT_ID;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                            ATTRIBUTES                             *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    int id;
    TaskStatus status = TaskStatus::OPEN;
    int priority;
    QString name;
    QDateTime deadline;
    QDateTime startTime;
    TimeSpan duration;
    Recurrence recurrence;
    QList<Task *> parent;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PRIVATE METHODS                          *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

public:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                           CONSTRUCTORS                            *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    Task(int priority, QString name, QDateTime deadline, QDateTime startTime, TimeSpan duration, Recurrence recurrence = Recurrence::NO_RECURRENCE); //, QList<Task *> parent = QList<Task *>());
    Task(const Task &) = delete;
    ~Task();

    /* * * * * * * * * * * * * * * * * * *\
    |*              GETTERS              *|
    \* * * * * * * * * * * * * * * * * * */

    int getId() const;
    int getPriority() const;

    TimeSpan getDuration() const;

    QDateTime getDeadline() const;
    QDateTime getStartTime() const;

    QList<Task *> getParents() const;

    QString getName() const;
    QString getRecurrenceString() const;
    QString getStatusString() const;

    Recurrence getRecurrence() const;

    TaskStatus getStatus() const;

    /* * * * * * * * * * * * * * * * * * *\
    |*              SETTERS              *|
    \* * * * * * * * * * * * * * * * * * */

    void setPriority(int);
    void setDuration(TimeSpan);
    void setDeadline(QDateTime);
    void setStartTime(QDateTime);
    void setName(QString);
    void setRecurrence(Recurrence);
    void setStatus(TaskStatus);

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PUBLIC METHODS                           *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    bool isCheckable() const;

    void addParent(Task *task);
    void deleteTask(Task task);
    void removeParent(Task *task);
    void updateTask(Task task); // TODO : hein, c'est débile non ?!

    QString readTask() const;
};

#endif // TASK_H
