#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <QVector>

#include "task.h"

class Task;

struct PonderatedTask
{
    Task *task;
    int priority;
};

class PriorityQueue
{
private:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                            ATTRIBUTES                             *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    QVector<PonderatedTask> pQueue;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PRIVATE METHODS                          *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    void heapify(int);
    void swap(int, int);

public:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                           CONSTRUCTORS                            *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    PriorityQueue();

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PUBLIC METHODS                           *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    bool empty() const;

    PonderatedTask pop();

    QVector<Task *> toQVector();

    void push(PonderatedTask);
};

#endif // PRIORITYQUEUE_H
