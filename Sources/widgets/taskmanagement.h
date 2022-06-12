#ifndef TASKMANAGEMENT_H
#define TASKMANAGEMENT_H

#include <QBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QProgressBar>
#include <QPushButton>
#include <QRadioButton>
#include <QVector>
#include <QWidget>
#include <QWindow>

#include <future>

#include "tabmodel.h"
#include "taskdialog.h"

class Task;

class TaskManagement : public TabModel
{
    Q_OBJECT

private:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                            ATTRIBUTES                             *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    QBoxLayout *topLayout, *mainLayout, *defaultLayout;
    TaskDialog *addTaskDialog, *modifyTask;
    QGridLayout *boardLayout;
    QLabel *lblTitle, *selectLabel, *statusLabel, *nameLabel, *dateLabel, *durationLabel, *progressionLabel;
    QPushButton *btnAddTask, *btnRemoveTask, *btnModifyTask;
    QVector<QLabel *> *lblNameTask, *lblDateTask, *lblDurationTask;
    QVector<QProgressBar *> *pgbProgressionTask;
    QVector<QPushButton *> *btnStatusTask;
    QVector<QRadioButton *> *radSelectTask;
    QVector<QVector<Task *>> tasks;

    QVector<int> tabTaskRadio;

    Task* selectedTask = nullptr;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PRIVATE METHODS                          *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    void addNewTask(int i);
    double definePG(Task * task, int nbSons) const;
    int defineAllSons(Task *task) const;
    int defineAllTime(Task *task) const;


public:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                           CONSTRUCTORS                            *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    TaskManagement(QWidget *_parent = nullptr);

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PUBLIC METHODS                           *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

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

    void deleteTask();
    void openNewWindow();
    void refresh();
    void radioButtonClicked(bool);
    void statusButtonPressed();
};

#endif // TASKMANAGEMENT_H
