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

    void tabChanged(int index);

signals:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
     *                           SIGNALS                           *
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    void refreshDashboard();
    void refreshTaskManagement();
};

#endif // TABWIDGET_H
