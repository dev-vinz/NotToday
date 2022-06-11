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

    //connect(taskManagement, &TaskManagement::taskAdded, dashboard, &Dashboard::newTaskAdded);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                            SLOTS                            *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


void TabWidget::tabChanged(int index)
{
    if (index == 0) emit refreshDashboard();
    if (index == 1) emit refreshTaskManagement();
}
