#include "tabwidget.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                           CONSTRUCTORS                            *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

TabWidget::TabWidget(QWidget *_parent) : QTabWidget(_parent)
{
    this->initialize();

    connect(this, &QTabWidget::currentChanged, this, &TabWidget::tabChanged);
    connect(this, &TabWidget::refreshDashboard, this->dashboard, &Dashboard::refresh);
    connect(this, &TabWidget::refreshTaskManagement, this->taskManagement, &TaskManagement::refresh);
    connect(this, &TabWidget::deleteTasks, this->dashboard, &Dashboard::deleteTDL);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                           PRIVATE                           *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void TabWidget::initialize()
{
    this->dashboard = new Dashboard;
    this->taskManagement = new TaskManagement;

    this->addTab(dashboard, tr("Dashboard"));
    this->addTab(taskManagement, tr("Task Management"));
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                            SLOTS                            *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


void TabWidget::tabChanged(int index)
{
    if (index == 0) emit refreshDashboard();
    if (index == 1) emit refreshTaskManagement();
}

//Delete the tdl and refresh both widgets
void TabWidget::deleteTask()
{
    emit deleteTasks();
    emit refreshDashboard();
    emit refreshTaskManagement();
}
