#include "task.h"

// Est appelé depuis la boite modale qui pour une nouvelle Task, les paramètres viennent des différentes zones de textes

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                           CONSTRUCTORS                            *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

Task::Task(TaskStatus status, int priority, QString name, QDateTime deadline, QDateTime startTime, TimeSpan duration, Recurrence recurrence, QList<Task *> parent)
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
        for (int i = 0; i < parent.size(); i++)
        {
            this->parent.append(parent.at(i));
        }
    }
}

Task::Task(const Task &task) : status(task.status), priority(task.priority), name(task.name), deadline(task.deadline), startTime(task.startTime), duration(task.duration), recurrence(task.recurrence)
{
    if (task.parent.size() != 0)
    {
        for (int i = 0; i < parent.size(); i++)
        {
            this->parent.append(parent.at(i));
        }
    }
}

Task::Task(const QJsonObject &json)
{
    this->read(json);
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

// Est appelé quand on veut afficher
QString Task::readTask() const
{
    QString message = "name: " + this->name + "\n " + "priority: " + QString::number(this->priority) + "\n " + "status: " + this->getStatusString() + "\n " + "deadline: " + Utils::dateToString(this->deadline) + "\n " + "startTime: " + Utils::dateToString(this->startTime) + "\n " + "reccurence: " + this->getRecurrenceString() + "\n ";

    message += this->duration.toString() + "\n";

    for (int i = 0; i < this->parent.size(); i++)
    {
        message += "Parent " + this->parent.at(i)->name + "\n";
    }

    return message;
}

/*!
 * \brief Task::read
 * \param json
 * \ref https://doc.qt.io/qt-5/qtcore-serialization-savegame-example.html
 */
void Task::read(const QJsonObject &json)
{
    if (json.contains("id") && json["id"].isDouble())
        this->id = json["id"].toInt();

    if (json.contains("status") && json["status"].isDouble())
        this->status = TaskStatus(json["status"].toInt());

    if (json.contains("priority") && json["priority"].isDouble())
        this->priority = json["priority"].toInt();

    if (json.contains("name") && json["name"].isString())
        this->name = json["name"].toString();

    if (json.contains("deadline") && json["deadline"].isString())
        this->deadline = QDateTime::fromString(json["deadline"].toString());

    if (json.contains("startTime") && json["startTime"].isString())
        this->startTime = QDateTime::fromString(json["startTime"].toString());

    if (json.contains("duration") && json["duration"].isString())
        this->duration = Utils::stringToTime(json["duration"].toString());

    if (json.contains("recurrence") && json["recurrence"].isDouble())
        this->recurrence = Recurrence(json["recurrence"].toInt());

    if (json.contains("parent") && json["parent"].isArray()) {
            QJsonArray parentArray = json["parent"].toArray();
            this->parent.clear();
            this->parent.reserve(parentArray.size());
            for (int parentIndex = 0; parentIndex < parentArray.size(); ++parentIndex) {
                QJsonObject taskObject = parentArray[parentIndex].toObject();
                Task *t = new Task(taskObject);
                this->parent.append(t);
            }
    }
}

void Task::write(QJsonObject &json) const
{
    json["id"] = this->id;
    json["status"] = this->status;
    json["priotity"] = this->priority;
    json["name"] = this->name;
    json["deadline"] = this->deadline.toString();
    json["startTime"] = this->startTime.toString();
    json["duration"] = this->duration.toString();
    json["recurrence"] = this->recurrence;
    QJsonArray parentArray;
    for (const Task *t : this->parent) {
        QJsonObject taskObject;
        t->write(taskObject);
        parentArray.append(taskObject);
    }
    json["parent"] = parentArray;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                          PRIVATE METHODS                          *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
