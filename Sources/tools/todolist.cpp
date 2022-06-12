#include "todolist.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                           CONSTRUCTORS                            *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

ToDoList::ToDoList()
{
}

ToDoList::~ToDoList()
{
    QList<Task *> keys = this->graph.keys();

    foreach (Task *t, keys)
    {
        this->removeTask(t);
    }
}

/* * * * * * * * * * * * * * * * * * *\
|*              GETTERS              *|
\* * * * * * * * * * * * * * * * * * */

Task *ToDoList::getTask(int id) const
{
    foreach (Task *t, this->getTasks())
    {
        if (t->getId() == id) return t;
    }

    return nullptr;
}

QList<Task *> ToDoList::getSonsOf(Task *task) const
{
    QList<Task *> sons;

    foreach (Task *t, this->getTasks())
    {
        foreach (Task *p, t->getParents())
        {
            if (p->getId() == task->getId())
            {
                sons.push_back(t);
            }
        }
    }

    return sons;
}

QList<Task *> ToDoList::getTasks() const
{
    return this->graph.keys();
}

QList<Task *> ToDoList::getToday() const
{
    QList<Task *> orderedTasks = this->run();
    QList<Task *> today;

    double totalMinutes = 0;

    foreach (Task *task, orderedTasks)
    {
        double timeNext = totalMinutes + task->getDuration().totalMinutes();

        if (task->getStatus() == TaskStatus::DONE) continue;

        if (timeNext > ToDoList::HOURS_IN_A_DAY_IN_MINUTES)
        {
            break;
        }
        else
        {
            today.push_back(task);
            totalMinutes = timeNext;
        }
    }

    return today;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                          PUBLIC METHODS                           *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

QVector<Task *> ToDoList::run() const
{
    /**
     * 1. Sort by deadline
     * 2. Make sure parents are before childrens
     * 3. If equality, task's priority first
     */

    PriorityQueue pQueue;

    foreach (Task *t, this->graph.keys())
    {
        QDateTime now = QDateTime::currentDateTime();

        int deadlinePriority = now.secsTo(t->getDeadline()) / 60 * DEADLINE_PRIORITY;
        int parentPriority = 0;

        foreach (const Task *son, this->getSonsOf(t))
        {
            if (son->getStatus() != TaskStatus::DONE)
            {
                parentPriority += PARENT_PRIORITY;
            }
        }

        PonderatedTask pTask;
        pTask.task = t;
        pTask.priority = deadlinePriority + parentPriority - t->getPriority();

        pQueue.push(pTask);
    }

    return pQueue.toQVector();
}

void ToDoList::addTask(Task *_task)
{
    if (!this->graph.contains(_task))
    {
        QVector<Task *> v;
        this->graph.insert(_task, v);
    }
    else
    {
        qDebug() << "Task already exists in graph";
    }
}

void ToDoList::removeTask(Task *_task)
{
    if (this->graph.contains(_task))
    {
        this->graph.remove(_task);

        QList<Task *> keys = this->graph.keys();

        foreach (Task *t, keys)
        {
            QList<Task *> dep = this->graph.value(t);

            if (dep.contains(_task))
            {
                this->removeDependence(t, _task);
            }
        }

        delete _task;
        _task = nullptr;
    }
    else
    {
        qDebug() << "Task doesn't exists in graph";
    }
}

#include <iostream>

void ToDoList::addDependence(Task *_child, Task *_parent)
{
    if (!this->graph[_child].contains(_parent))
    {
        this->graph[_child].append(_parent);

        _child->addParent(_parent);
    }
    else
    {
        qDebug() << "Dependence already exists in graph";
    }
}

void ToDoList::removeDependence(Task *_child, Task *_parent)
{
    if (this->graph[_child].contains(_parent))
    {
        this->graph[_child].removeOne(_parent);

        _child->removeParent(_parent);
    }
    else
    {
        qDebug() << "Dependence doesn't exists in graph";
    }
}
/*!
 * \brief ToDoList::read
 * \param json
 * \ref https://doc.qt.io/qt-5/qtcore-serialization-savegame-example.html
 */
void ToDoList::read(const QJsonObject &json)
{
    if(json.contains("graph") && json["graph"].isArray())
    {

    }
}

void ToDoList::write(QJsonObject &json) const
{
    QMapIterator<Task*, QVector<Task *>> i(this->graph);
    int j = 0;
    while (i.hasNext())
    {
        i.next();
        QJsonArray dependenciesArray;
        QJsonObject originTask;
        i.key()->write(originTask);
        dependenciesArray.append(originTask);
        for (const Task * t : i.value())
        {
            QJsonObject taskObject;
            t->write(taskObject);
            dependenciesArray.append(taskObject);

        }
        json[QChar(j)] = dependenciesArray;
        j++;
    }
}



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                          PRIVATE METHODS                          *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
