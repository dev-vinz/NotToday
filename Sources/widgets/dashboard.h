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

    QFile file;

    //Layouts
    QBoxLayout *mainLayout, *defaultLayout, *taskLayout;
    QGridLayout *boardLayout;

    // Header of the table
    QLabel *lblTitle, *selectLabel, *statusLabel, *nameLabel, *dateLabel, *durationLabel, *progressionLabel;

    //each values of the tasks are in Vector, the is is the same than the one gotten from getToday()
    QVector<QLabel *> *lblNameTask, *lblDateTask, *lblDurationTask;
    QVector<QProgressBar *> *pgbProgressionTask;
    QVector<QPushButton *> *btnStatusTask;
    QVector<QRadioButton *> *radSelectTask;
    QVector<Task *> tasks;

    //When we display the tasks, they are put in another Vector to get the id in the list
    QVector<int> tabTaskRadio;

    Task* selectedTask = nullptr;


    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PRIVATE METHODS                          *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    void addNewTask(int i);
    void addTask();

public:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                           CONSTRUCTORS                            *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    Dashboard(QWidget *_parent = nullptr);

protected:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                         PROTECTED METHODS                         *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    //foreach task call the displayTask
    void displayTasks() override;

    //the indice is the corresponding place in the QVectors in the attributes
    void displayTask(Task *task, int indice) const override;

    //called in the refresh to clear everything
    void initialize() override;

public slots:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
     *                            SLOTS                            *
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    void refresh();
    //Used to know wich task is linked with wich radiobutton
    void radioButtonClicked(bool);
    //When the user click the status it change from OPEN to DOING and from DOING to DONE
    void statusButtonPressed();

};

#endif // DASHBOARD_H
