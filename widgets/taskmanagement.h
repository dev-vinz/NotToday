#ifndef TASKMANAGEMENT_H
#define TASKMANAGEMENT_H

#include <QObject>
#include <QWidget>
#include <QWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>
#include <QMainWindow>

#include "tabmodel.h"

class Task;

class TaskManagement : public TabModel
{
    Q_OBJECT

private:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                            ATTRIBUTES                             *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    QBoxLayout *topLayout, *mainLayout, *defaultLayout;
    QDialog *addTask, *modifyTask;
    QGridLayout *boardLayout;
    QLabel *lblTitle, *selectLabel, *statusLabel, *nameLabel, *dateLabel, *durationLabel, *progressionLabel;
    QPushButton *btnAddTask, *btnRemoveTask, *btnModifyTask;

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

    void displayTask(Task task, int indice) const override;
    void initialize() override;

public slots:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
     *                            SLOTS                            *
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    void openNewWindow();
};

#endif // TASKMANAGEMENT_H
