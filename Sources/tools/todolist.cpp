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

        if (timeNext > ToDoList::HOURS_IN_A_DAY_IN_MINUTES)
        {
            // Temps en minutes
            double overflow = timeNext - ToDoList::HOURS_IN_A_DAY_IN_MINUTES;
            double available = task->getDuration().totalMinutes() - overflow;

            Task *copy = new Task(*task);

            // TODO : Modifier task et mettre le temps overflow
            task->setDuration(TimeSpan::fromMinutes(overflow));

            // TODO : Modifier la copy et mettre le temps disponible
            copy->setDuration(TimeSpan::fromMinutes(available));

            today.push_back(copy);

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

        int deadlinePriority = now.secsTo(t->getDeadline()) * DEADLINE_PRIORITY;
        int parentPriority = 0;

        foreach (const Task *parent, t->getParents())
        {
            if (parent->getStatus() != TaskStatus::DONE)
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

void ToDoList::addDependence(Task *_taskSrc, Task *_taskDest)
{
    if (!this->graph[_taskSrc].contains(_taskDest))
    {
        this->graph[_taskSrc].append(_taskDest);

        _taskDest->addParent(_taskSrc);
    }
    else
    {
        qDebug() << "Dependence already exists in graph";
    }
}

void ToDoList::removeDependence(Task *_taskSrc, Task *_taskDest)
{
    if (this->graph[_taskSrc].contains(_taskDest))
    {
        this->graph[_taskSrc].removeOne(_taskDest);

        _taskDest->removeParent(_taskSrc);
    }
    else
    {
        qDebug() << "Dependence doesn't exists in graph";
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                          PRIVATE METHODS                          *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
