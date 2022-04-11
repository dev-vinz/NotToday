#ifndef TABMODEL_H
#define TABMODEL_H

#include <QObject>
#include <QTabBar>
#include <QWidget>

#include "..\tools\task.h"

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
    QVector<Task> tasks;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                         PROTECTED METHODS                         *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    Task createTask();

    void addNewTask(int i);
    void addTask();
    void displayTasks();

    void virtual displayTask(Task task, int indice) const = 0;
    void virtual initialize() = 0;
};

#endif // TABMODEL_H
