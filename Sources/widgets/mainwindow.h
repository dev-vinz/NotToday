#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>

#include "tabwidget.h"

class TabWidget;

class MainWindow : public QMainWindow
{
private:
    QAction *actAbout;
    TabWidget *widget;

    void createActions();
    void createMenuBar();
    void initialize();

public:
    MainWindow(QWidget *_parent = nullptr);

public slots:
    void showStatusBar(const QString msg);
};

#endif // MAINWINDOW_H
