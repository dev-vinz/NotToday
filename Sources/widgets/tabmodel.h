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

    //The dashboard and the Taskmodel both have the tdl
    static ToDoList tdl;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                         PROTECTED METHODS                         *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    void virtual displayTask(Task *task, int indice) const = 0;
    void virtual displayTasks() = 0;
    void virtual initialize() = 0;

    //Recursive algorithme to have the percentage of th progression bar
    double definePG(Task * task, int nbSons) const;
    int defineAllSons(Task *task) const;
    int defineAllTime(Task *task) const;

public slots:
    void deleteTDL();
};

#endif // TABMODEL_H
