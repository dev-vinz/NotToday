#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QObject>
#include <QTabWidget>
#include <QWidget>

#include "dashboard.h"
#include "mainwindow.h"
#include "taskmanagement.h"

class MainWindow;

class TabWidget : public QTabWidget
{
    Q_OBJECT

    friend MainWindow;

private:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                            ATTRIBUTES                             *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    Dashboard *dashboard;
    TaskManagement *taskManagement;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PRIVATE METHODS                          *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    void initialize();

public:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                           CONSTRUCTORS                            *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    TabWidget(QWidget *_parent = nullptr);

public slots:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
     *                            SLOTS                            *
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    //refresh Dashboard or TaskManagement
    void tabChanged(int index);

    //the slots call the signals deleteTasks and the refreshs for both Dashboard and TaskManagement
    void deleteTask();

signals:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
     *                           SIGNALS                           *
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    void deleteTasks();
    void refreshDashboard();
    void refreshTaskManagement();

};

#endif // TABWIDGET_H
