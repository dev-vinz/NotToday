#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QAction>
#include <QFile>
#include <QObject>
#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QProgressBar>
#include <QRadioButton>
#include <QLabel>

#include "tabmodel.h"

class Dashboard : public TabModel
{
    Q_OBJECT

private:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                            ATTRIBUTES                             *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    QAction *actSave, *actOpen, *actNew;
    QBoxLayout *mainLayout, *defaultLayout, *taskLayout;
    QFile file;
    QGridLayout *boardLayout;
    QLabel *lblTitle, *selectLabel, *statusLabel, *nameLabel, *dateLabel, *durationLabel, *progressionLabel;
    QVector<QLabel *> *lblNameTask, *lblDateTask, *lblDurationTask;
    QVector<QProgressBar *> *pgbProgressionTask;
    QVector<QPushButton *> *btnStatusTask;
    QVector<QRadioButton *> *radSelectTask;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PRIVATE METHODS                          *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    void addNewTask(int i);
    void addTask();
    void createActions();
    void displayTasks();

public:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                           CONSTRUCTORS                            *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    Dashboard(QWidget *_parent = nullptr);

    /* * * * * * * * * * * * * * * * * * *\
    |*              GETTERS              *|
    \* * * * * * * * * * * * * * * * * * */

    QAction *getNewAction() const;
    QAction *getOpenAction() const;
    QAction *getSaveAction() const;

protected:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                         PROTECTED METHODS                         *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    void displayTask(Task task, int indice) const override;
    void initialize() override;
};

#endif // DASHBOARD_H
