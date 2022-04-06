#include "todolist.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                           CONSTRUCTORS                            *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

ToDoList::ToDoList()
{

}

ToDoList::~ToDoList()
{
    foreach (Task *t, this->graph.keys())
    {
        this->removeTask(t);
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                          PUBLIC METHODS                           *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

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

        foreach (Task *t, this->graph.keys())
        {
            this->removeDependence(t, _task);
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
    }
    else
    {
        qDebug() << "Dependence doesn't exists in graph";
    }
}

void ToDoList::runCoffmanGraham() const
{
    QVector<Task *> taskList = this->coffman();

    return this->graham(taskList);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                          PRIVATE METHODS                          *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

QVector<Task *> ToDoList::coffman() const
{

}

void ToDoList::graham(QVector<Task *> _tasks) const
{

}
