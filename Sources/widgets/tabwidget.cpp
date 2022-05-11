#include "tabwidget.h"

TabWidget::TabWidget(QWidget *_parent) : QTabWidget(_parent)
{
    this->initialize();
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
