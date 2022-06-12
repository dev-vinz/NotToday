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

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                         PROTECTED METHODS                         *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void TabModel::addNewTask(int i)
{
    // TODO
}

void TabModel::addTask()
{
    // TODO
}



void TabModel::deleteTDL()
{
    QVector<Task *> tasks = tdl.run();

    foreach(Task * task, tasks)
    {
        tdl.removeTask(task);
    }
}
