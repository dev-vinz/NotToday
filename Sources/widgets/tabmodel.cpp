#include "tabmodel.h"
#include <QMessageBox>

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                            ATTRIBUTES                             *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

ToDoList TabModel::tdl;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                           CONSTRUCTORS                            *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

TabModel::TabModel(QWidget *_parent) : QTabBar(_parent)
{
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                           PRIVATE                           *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int TabModel::defineAllTime(Task *task) const
{
    QList<Task *> sons = TabModel::tdl.getSonsOf(task);
    int value = task->getDuration().totalMinutes();
    if(sons.size()<=0)
    {
        return value;
    }

    foreach(Task * son, sons)
    {
        value += defineAllTime(son);
    }
    return value;
}

int TabModel::defineAllSons(Task *task) const
{
    QList<Task *> sons = TabModel::tdl.getSonsOf(task);
    int value = 0;
    if(sons.size()<=0)
    {
        return 0;
    }

    foreach(Task * son, sons)
    {
        value += 1 + defineAllSons(son);
    }
    return value;
}

double TabModel::definePG(Task *task, int time) const
{
    QList<Task *> sons = TabModel::tdl.getSonsOf(task);
    double value = 0;

    if (task->getStatus() == TaskStatus::DONE)
    {
        value += 100.0 / time*task->getDuration().totalMinutes();
    }

    if(sons.size()<=0)
    {
        return value;
    }

    foreach(Task * son, sons)
    {
        value += definePG(son,time);
    }
    return value;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                            SLOTS                            *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void TabModel::deleteTDL()
{
    QVector<Task *> tasks = tdl.run();

    foreach(Task * task, tasks)
    {
        tdl.removeTask(task);
    }
}
