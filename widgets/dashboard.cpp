#include "dashboard.h"

Dashboard::Dashboard(QWidget *_parent) : TabModel(_parent)
{
    this->initialize();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                           PRIVATE                           *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Dashboard::createActions()
{
    this->actSave = new QAction(tr("&Save"));
    this->actSave->setShortcut(tr("CTRL+S"));
    this->actSave->setStatusTip(tr("Save file in your computer"));

    this->actOpen = new QAction(tr("&Open"));
    this->actOpen->setShortcut(tr("CTRL+O"));
    this->actOpen->setStatusTip(tr("Open file from your computer"));

    this->actNew = new QAction(tr("&New"));
    this->actNew->setShortcut(tr("CTRL+N"));
    this->actNew->setStatusTip(tr("Create a new blank file"));
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                          PROTECTED                          *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


void Dashboard::initialize()
{
    this->createActions();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                           PUBLIC                            *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

QAction *Dashboard::getNewAction() const
{
    return this->actNew;
}

QAction *Dashboard::getOpenAction() const
{
    return this->actOpen;
}

QAction *Dashboard::getSaveAction() const
{
    return this->actSave;
}
