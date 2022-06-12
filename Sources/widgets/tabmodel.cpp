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
