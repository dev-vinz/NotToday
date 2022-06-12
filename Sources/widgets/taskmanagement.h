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

    //Layout
    QBoxLayout *topLayout, *mainLayout, *defaultLayout;
    QGridLayout *boardLayout;

    //Dialog for modify a Task or add a new one
    TaskDialog *addTaskDialog, *modifyTask;

    //Labels
    QLabel *lblTitle, *selectLabel, *statusLabel, *nameLabel, *dateLabel, *durationLabel, *progressionLabel;

    //Buttons
    QPushButton *btnAddTask, *btnRemoveTask, *btnModifyTask;

    //each values of the tasks are in Vector, the is is the same than the one gotten from getToday()

    QVector<QLabel *> *lblNameTask, *lblDateTask, *lblDurationTask;
    QVector<QProgressBar *> *pgbProgressionTask;
    QVector<QPushButton *> *btnStatusTask;
    QVector<QRadioButton *> *radSelectTask;
    QVector<QVector<Task *>> tasks;

    //When we display the tasks, they are put in another Vector to get the id in the list
    QVector<int> tabTaskRadio;

    Task* selectedTask = nullptr;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PRIVATE METHODS                          *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    void addNewTask(int i);


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
