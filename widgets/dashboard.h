#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QAction>
#include <QFile>
#include <QObject>
#include <QWidget>

#include "tabmodel.h"

class Dashboard : public TabModel
{
    Q_OBJECT

private:
    QAction *actSave, *actOpen, *actNew;
    QFile file;

    void createActions();

public:
    Dashboard(QWidget *_parent = nullptr);

    QAction *getNewAction() const;
    QAction *getOpenAction() const;
    QAction *getSaveAction() const;

protected:
    //void displayTasks() const override;
    void initialize() override;
};

#endif // DASHBOARD_H
