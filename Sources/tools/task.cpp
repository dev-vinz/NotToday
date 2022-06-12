#include "task.h"

// Est appelé depuis la boite modale qui pour une nouvelle Task, les paramètres viennent des différentes zones de textes

int Task::CURRENT_ID = 0;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                           CONSTRUCTORS                            *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

Task::Task(int priority, QString name, QDateTime deadline, QDateTime startTime, TimeSpan duration, Recurrence recurrence)
{
    this->id = Task::CURRENT_ID++;
    this->status = status;
    this->priority = priority;
    this->name = name;
    this->deadline = deadline;
    this->startTime = startTime;
    this->recurrence = recurrence;
    this->duration = duration;
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
