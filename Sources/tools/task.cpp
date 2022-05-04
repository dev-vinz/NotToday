#include "task.h"

//Est appelé depuis la boite modale qui pour une nouvelle Task, les paramètres viennent des différentes zones de textes

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                           CONSTRUCTORS                            *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

Task::Task(TaskStatus status, int priority, QString name, QDateTime deadline, QDateTime startTime, TimeSpan duration, Recurrence recurrence, QList<Task*> parent)
{
    this->status = status;
    this->priority = priority;
    this->name = name;
    this->deadline = deadline;
    this->startTime = startTime;
    this->recurrence = recurrence;
    this->duration = duration;

    if (parent.size() != 0)
    {
        for(int i = 0; i < parent.size(); i++)
        {
            this->parent.append(parent.at(i));
        }
    }
}

Task::Task(const Task& task) : status(task.status), priority(task.priority), name(task.name), deadline(task.deadline), startTime(task.startTime), duration(task.duration), recurrence(task.recurrence)
{
    if (task.parent.size() != 0)
    {
        for(int i = 0; i < parent.size(); i++)
        {
            this->parent.append(parent.at(i));
        }
    }
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
/*!
 * @brief test DOXYGEN .cpp looooooooool
 * @return
 */
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
    switch (this->status) {
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

void Task::setDuration(TimeSpan ts)
{
    this->duration = ts;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                          PUBLIC METHODS                           *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Task::addParent(Task *task)
{
    this->parent.append(task);
}

bool Task::isCheckable() const
{
    // TODO
    return false;
}

void Task::deleteTask(Task task)
{
    // TODO
}

void Task::removeParent(Task *task)
{
    this->parent.remove(this->parent.indexOf(task));
}

void Task::updateTask(Task task)
{
    this->status = task.status;
    this->priority = task.priority;
    this->name = task.name;
    this->deadline = task.deadline;
    this->startTime = task.startTime;
    this->recurrence = task.recurrence;
    this->duration = task.duration;

    this->parent.clear();

    for (int i = 0; i < task.parent.size(); i++)
    {
        this->addParent(task.parent.at(i));
    }
}

//Est appelé quand on veut afficher
QString Task::readTask() const
{
    QString message = "name: " + this->name + "\n "
                    + "priority: " + QString::number(this->priority) + "\n "
                    + "status: " + this->getStatusString() + "\n "
                    + "deadline: " + Utils::dateToString(this->deadline) + "\n "
                    + "startTime: " + Utils::dateToString(this->startTime) + "\n "
                    + "reccurence: " + this->getRecurrenceString() + "\n ";

    message += this->duration.toString() + "\n";

    for (int i = 0; i < this->parent.size(); i++)
    {
        message += "Parent " + this->parent.at(i)->name + "\n";
    }

    return message;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                          PRIVATE METHODS                          *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

