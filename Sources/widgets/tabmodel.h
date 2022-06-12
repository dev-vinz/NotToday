#ifndef TABMODEL_H
#define TABMODEL_H

#include <QObject>
#include <QTabBar>
#include <QWidget>

#include "../tools/todolist.h"

class TabModel : public QTabBar
{
    Q_OBJECT

public:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                           CONSTRUCTORS                            *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    TabModel(QWidget *_parent);

protected:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                            ATTRIBUTES                             *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    static ToDoList tdl;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                         PROTECTED METHODS                         *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    void virtual displayTask(Task *task, int indice) const = 0;
    void virtual displayTasks() = 0;
    void virtual initialize() = 0;


public slots:
    void deleteTDL();
};

#endif // TABMODEL_H
