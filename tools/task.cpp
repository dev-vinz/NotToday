#include "task.h"

//Est appelé depuis la boite modale qui pour une nouvelle Task, les paramètres viennent des différentes zones de textes

Task::Task(TaskStatus status, int priority, QString name, QDateTime deadline, QDateTime startTime, Recurrence recurrence, QDateTime duration,QList<Task*> *parent)
{
    this->status=status;
    this->priority=priority;
    this->name=name;
    this->deadline=deadline;
    this->startTime=startTime;
    this->recurrence=recurrence;
    this->duration=duration;
    this->parent = new QList<Task*>;
    if(parent->size()==0)
    {

    }else
    {
    for(int i=0;i<parent->size();i++)
    {
        this->parent->append(parent->at(i));
    }
    }
}

/*Task Task::createTask(TaskStatus status, int priority, QString name, QDateTime deadline, QDateTime startTime, Recurrence recurrence, QDateTime duration , QList<Task*> *parent)
{
    return Task(status,priority,name,deadline,startTime,recurrence,duration,parent);
}*/

//Est appelé quand on veut afficher
QString Task::readTask()
{
    QString message = "name: " + this->name + "\n "
                    + "priority: " + QString::number(this->priority) + "\n "
                    + "status: " + getTaskStatus(this->status) + "\n "
                    + "deadline: " + this->DateToString(this->deadline) + "\n "
                    + "startTime: " + this->DateToString(this->startTime) + "\n "
                    + "reccurence: " + getRecurrence(this->recurrence) + "\n ";

    message += this->DurationToString() + "\n";
    /*
    foreach(Task* str, *this->parent)
    {
        message += "Parent " + str->name + "\n";
    }*/
    for(int i=0;i<this->parent->size();i++)
    {
        message += "Parent " + this->parent->at(i)->name + "\n";
    }
    return message;
}

QString Task::DurationToString()
{
    QString message = "";
    if((this->duration.date()==QDate(0,0,0)))
    {
        this->duration=this->duration.addDays(1);
        message+=this->duration.toString("HH:mm::ss");
        this->duration.setDate(QDate(0,0,0));
    }else
    {
        message+= this->duration.toString("yyyy-MM-dd");
        message+= this->duration.toString("HH:mm::ss");
    }
    return message;
}
QString Task::DateToString(QDateTime date)
{
    return date.toString("yyyy-MM-dd");
}
void Task::updateTask(Task task)
{
    this->setStatus(task.status);
    this->setPriority(task.priority);
    this->setName(task.name);
    this->setDeadline(task.deadline);
    this->setStartTime(task.startTime);
    this->setRecurrence(task.recurrence);
    this->setDuration(task.duration);
    /*
    foreach(Task* task, task.parent)
    {
        this->addParent(task);
    }*/
    for(int i=0;i<task.parent->size();i++)
    {
        this->addParent(task.parent->at(i));
    }
}
void Task::deleteTask(Task task)
{

}

void Task::setStatus(TaskStatus status)
{
    this->status=status;
}
void Task::setPriority(int priority)
{
    this->priority=priority;
}
void Task::setName(QString name)
{
    this->name=name;
}
void Task::setDeadline(QDateTime deadline)
{
    this->deadline=deadline;
}
void Task::setStartTime(QDateTime startTime)
{
    this->startTime=startTime;
}
void Task::setRecurrence(Recurrence recurrence)
{
    this->recurrence=recurrence;
}
void Task::setDuration(QDateTime duration)
{
    this->duration=duration;
}
void Task::addParent(Task* task)
{
    this->parent->append(task);
}
void Task::removeParent(Task* task)
{
    this->parent->remove(this->parent->indexOf(task));
}

QString Task::getRecurrence(Recurrence recurrence)
{
    switch (recurrence) {
    case Recurrence::everyDay:
        return "Every Day";
    case Recurrence::everyTwoWeek:
        return "Every Two Week";
    case Recurrence::everyWeek:
        return "Every Week";
    case Recurrence::noRecurrence:
        return "No Recurrence";
    default:
        return "ERROR RECURRENCE";
    }
}

QString Task::getTaskStatus(TaskStatus status)
{
    switch (status) {
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
