#ifndef TODOLIST_H
#define TODOLIST_H

#include <QMap>
#include <QVector>

#include "priorityqueue.h"
#include "task.h"

#define DEADLINE_PRIORITY 10
#define PARENT_PRIORITY 5

class Task;

class ToDoList
{
private:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                            ATTRIBUTES                             *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    static constexpr int HOURS_IN_A_DAY_IN_MINUTES = 8 * 60;

    QMap<Task *, QVector<Task *>> graph;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PRIVATE METHODS                          *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

public:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                           CONSTRUCTORS                            *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    ToDoList();
    ~ToDoList();

    /* * * * * * * * * * * * * * * * * * *\
    |*              GETTERS              *|
    \* * * * * * * * * * * * * * * * * * */

    Task *getTask(int id) const;

    QList<Task *> getSonsOf(Task *task) const;

    QList<Task *> getTasks() const;
    QList<Task *> getToday() const;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PUBLIC METHODS                           *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    QVector<Task *> run() const;

    void addTask(Task *);
    void removeTask(Task *);

    void addDependence(Task *_child, Task *_parent);
    void removeDependence(Task *_child, Task *_parent);
};

#endif // TODOLIST_H
