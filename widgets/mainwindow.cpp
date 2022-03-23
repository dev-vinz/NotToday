#include "mainwindow.h"

MainWindow::MainWindow(QWidget *_parent) : QMainWindow(_parent)
{
    this->initialize();
    this->createActions();
    this->createMenuBar();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                           PRIVATE                           *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void MainWindow::createActions()
{
    this->actAbout = new QAction(tr("&About"));
}

void MainWindow::createMenuBar()
{
    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(this->widget->dashboard->getNewAction());
    file->addSeparator();
    file->addAction(this->widget->dashboard->getOpenAction());
    file->addAction(this->widget->dashboard->getSaveAction());

    menuBar()->addAction(this->actAbout);
}

void MainWindow::initialize()
{
    resize(800, 600);
    setWindowTitle(tr("NotToday"));

    statusBar()->showMessage("");

    this->widget = new TabWidget;
    setCentralWidget(this->widget);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                            SLOTS                            *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void MainWindow::showStatusBar(const QString msg)
{
    statusBar()->showMessage(msg);
}
