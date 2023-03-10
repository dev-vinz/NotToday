#include "mainwindow.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                           CONSTRUCTORS                            *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

MainWindow::MainWindow(QWidget *_parent) : QMainWindow(_parent)
{
    this->initialize();
    this->createActions();
    this->createMenuBar();

    connect(actAbout, &QAction::triggered, this, &MainWindow::about);
    connect(actNew, &QAction::triggered, this, &MainWindow::newTdl);
    connect(actOpen, &QAction::triggered, this, &MainWindow::open);
    connect(actSave, &QAction::triggered, this, &MainWindow::save);

    connect(this, &MainWindow::deleteAll, this->widget, &TabWidget::deleteTask);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                           PRIVATE                           *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void MainWindow::createActions()
{
    this->actAbout = new QAction(tr("&About"));

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

void MainWindow::createMenuBar()
{
    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(this->actNew);
    file->addSeparator();
    file->addAction(this->actOpen);
    file->addAction(this->actSave);

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

void MainWindow::about()
{
    QMessageBox::information(NULL, "About", "Projet fait dans le cadre du P2 du semestre d'Automne.\nNot-Today est une application de gestion de temps et de t??ches.\n Auteurs:\n\tVincent Jeannin\n\tBenjamin Mouchet\n\tGuillaume Mouchet");
}

void MainWindow::newTdl()
{
    emit deleteAll();
}

//Not implemented yet
void MainWindow::save()
{
    QMessageBox::information(NULL, "Save", "Fonctionnalit?? pas encore impl??ment??e, elle permettra de garder l\'??tat entre chaque fermeture de l\'application");
}

void MainWindow::open()
{
    QMessageBox::information(NULL, "Open", "Fonctionnalit?? pas encore impl??ment??e, elle permettra de r??cup??rer l\'??tat de l'application");
}
