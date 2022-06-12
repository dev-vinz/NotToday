#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QAction>
#include <QBoxLayout>
#include <QFile>
#include <QLabel>
#include <QObject>
#include <QProgressBar>
#include <QPushButton>
#include <QRadioButton>
#include <QWidget>

#include <QMessageBox>

#include "tabmodel.h"

class Dashboard : public TabModel
{
    Q_OBJECT

private:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                            ATTRIBUTES                             *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    QBoxLayout *mainLayout, *defaultLayout, *taskLayout;
    QFile file;
    QGridLayout *boardLayout;
    QLabel *lblTitle, *selectLabel, *statusLabel, *nameLabel, *dateLabel, *durationLabel, *progressionLabel;
    QVector<QLabel *> *lblNameTask, *lblDateTask, *lblDurationTask;
    QVector<QProgressBar *> *pgbProgressionTask;
    QVector<QPushButton *> *btnStatusTask;
    QVector<QRadioButton *> *radSelectTask;
    QVector<Task *> tasks;

    QVector<int> tabTaskRadio;

    Task* selectedTask = nullptr;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PRIVATE METHODS                          *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    void addNewTask(int i);
    void addTask();
    double definePG(Task * task, int nbSons) const;
    int defineAllSons(Task *task) const;
    int defineAllTime(Task *task) const;
public:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                           CONSTRUCTORS                            *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    Dashboard(QWidget *_parent = nullptr);

protected:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                         PROTECTED METHODS                         *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    void displayTask(Task *task, int indice) const override;
    void displayTasks() override;
    void initialize() override;

public slots:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
     *                            SLOTS                            *
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    void refresh();
    void radioButtonClicked(bool);
    void statusButtonPressed();

};

#endif // DASHBOARD_H
