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
    TabModel(QWidget *_parent);

protected:
    //void virtual displayTasks() const = 0;
    QVector<Task> tasks;
    Task createTask();
    void displayTask(Task task, int indice);
    void displayTasks();
    void addTask();
    void addNewTask(int i);
    void virtual initialize() = 0;
};

#endif // TABMODEL_H
