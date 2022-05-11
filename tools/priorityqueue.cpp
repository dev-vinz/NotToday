#include "priorityqueue.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                           CONSTRUCTORS                            *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

PriorityQueue::PriorityQueue()
{
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                          PUBLIC METHODS                           *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

bool PriorityQueue::empty() const
{
    return this->pQueue.empty();
}

PonderatedTask PriorityQueue::pop()
{
    int size = this->pQueue.size();

    PonderatedTask front = this->pQueue.front();
    this->pQueue.pop_front();

    for (int i = size / 2 - 1; i >= 0; i--)
    {
        this->heapify(i);
    }

    return front;
}

void PriorityQueue::push(PonderatedTask _pTask)
{
    int size = this->pQueue.size();

    this->pQueue.push_back(_pTask);

    if (size != 0)
    {
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            this->heapify(i);
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                          PRIVATE METHODS                          *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void PriorityQueue::heapify(int _root)
{
    int size = this->pQueue.size();

    int smallest = _root;
    int leftSon = 2 * _root + 1;
    int rightSon = leftSon + 1;

    if (leftSon < size && this->pQueue[leftSon].priority <= this->pQueue[smallest].priority)
    {
        smallest = leftSon;
    }

    if (rightSon < size && this->pQueue[rightSon].priority <= this->pQueue[smallest].priority)
    {
        smallest = rightSon;
    }

    if (smallest != _root)
    {
        this->swap(_root, smallest);
        this->heapify(smallest);
    }
}

void PriorityQueue::swap(int _i, int _j)
{
    PonderatedTask temp = this->pQueue[_i];
    this->pQueue[_i] = this->pQueue[_j];
    this->pQueue[_j] = temp;
}
