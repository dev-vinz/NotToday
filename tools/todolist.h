#ifndef TODOLIST_H
#define TODOLIST_H

#include <QMap>
#include <QVector>

#include "task.h"

class ToDoList
{
private:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                            ATTRIBUTES                             *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    QMap<Task *, QVector<Task *>> graph;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PRIVATE METHODS                          *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    QVector<Task *> coffman() const;
    void graham(QVector<Task *>) const;

public:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                           CONSTRUCTORS                            *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    ToDoList();
    ~ToDoList();

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PUBLIC METHODS                           *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    void addTask(Task *);
    void removeTask(Task *);

    void addDependence(Task *, Task *);
    void removeDependence(Task *, Task *);

    void runCoffmanGraham() const;
};

#endif // TODOLIST_H
