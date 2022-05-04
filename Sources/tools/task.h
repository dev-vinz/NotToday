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

    Task(TaskStatus status, int priority, QString name, QDateTime deadline, QDateTime startTime, TimeSpan duration, Recurrence recurrence = Recurrence::NO_RECURRENCE, QList<Task *> parent = QList<Task *>());
    Task(const Task &);
    ~Task();

    /* * * * * * * * * * * * * * * * * * *\
    |*              GETTERS              *|
    \* * * * * * * * * * * * * * * * * * */
    /*!
     * @brief Test DOXYGEN .h
     * @return
     */
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

    void setDuration(TimeSpan);

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PUBLIC METHODS                           *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    bool isCheckable() const;

    void addParent(Task* task);
    void deleteTask(Task task);
    void removeParent(Task* task);
    void updateTask(Task task); // TODO : hein, c'est débile non ?!

    QString readTask() const;
};

#endif // TASK_H
