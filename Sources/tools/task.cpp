#include "task.h"

// Est appelé depuis la boite modale qui pour une nouvelle Task, les paramètres viennent des différentes zones de textes

int Task::CURRENT_ID = 0;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                           CONSTRUCTORS                            *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

Task::Task(int priority, QString name, QDateTime deadline, QDateTime startTime, TimeSpan duration, Recurrence recurrence)
{
    this->id = Task::CURRENT_ID++;
    this->priority = priority;
    this->name = name;
    this->deadline = deadline;
    this->startTime = startTime;
    this->recurrence = recurrence;
    this->duration = duration;
}

Task::~Task()
{
}

/* * * * * * * * * * * * * * * * * * *\
|*              GETTERS              *|
\* * * * * * * * * * * * * * * * * * */

int Task::getId() const
{
    return this->id;
}

int Task::getPriority() const
{
    return this->priority;
}

TimeSpan Task::getDuration() const
{
    return this->duration;
}

QDateTime Task::getDeadline() const
{
    return this->deadline;
}

QDateTime Task::getStartTime() const
{
    return this->startTime;
}

QList<Task *> Task::getParents() const
{
    return this->parent;
}

QString Task::getName() const
{
    return this->name;
}

QString Task::getRecurrenceString() const
{
    switch (this->recurrence)
    {
    case Recurrence::EVERY_DAY:
        return "Every Day";
    case Recurrence::EVERY_TWO_WEEKS:
        return "Every Two Week";
    case Recurrence::EVERY_WEEK:
        return "Every Week";
    case Recurrence::NO_RECURRENCE:
        return "No Recurrence";
    default:
        return "ERROR RECURRENCE";
    }
}

QString Task::getStatusString() const
{
    switch (this->status)
    {
    case TaskStatus::DOING:
        return "Doing";
    case TaskStatus::DONE:
        return "Done";
    case TaskStatus::LOCKED:
        return "Locked";
    case TaskStatus::OPEN:
        return "Open";
    default:
        return "ERROR STATUS";
    }
}

Recurrence Task::getRecurrence() const
{
    return this->recurrence;
}

TaskStatus Task::getStatus() const
{
    return this->status;
}

/* * * * * * * * * * * * * * * * * * *\
|*              SETTERS              *|
\* * * * * * * * * * * * * * * * * * */

void Task::setPriority(int priority)
{
    this->priority = priority;
}

void Task::setDuration(TimeSpan ts)
{
    this->duration = ts;
}

void Task::setDeadline(QDateTime date)
{
    this->deadline = date;
}

void Task::setStartTime(QDateTime time)
{
    this->startTime = time;
}

void Task::setName(QString name)
{
    this->name = name;
}

void Task::setRecurrence(Recurrence recurrence)
{
    this->recurrence = recurrence;
}

void Task::setStatus(TaskStatus status)
{
    this->status = status;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                          PUBLIC METHODS                           *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Task::addParent(Task *task)
{
    task->setStatus(TaskStatus::LOCKED);
    this->parent.append(task);
}

void Task::removeParent(Task *task)
{
    this->parent.remove(this->parent.indexOf(task));
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                          PRIVATE METHODS                          *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
