#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QObject>
#include <QTabWidget>
#include <QWidget>

#include "dashboard.h"
#include "taskmanagement.h"

#include "mainwindow.h"

class MainWindow;

class TabWidget : public QTabWidget
{
    Q_OBJECT

    friend MainWindow;

private:
    Dashboard *dashboard;
    TaskManagement *taskManagement;

    void initialize();

public:
    TabWidget(QWidget *_parent = nullptr);
};

#endif // TABWIDGET_H
