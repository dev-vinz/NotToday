#ifndef TASKDIALOG_H
#define TASKDIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>
#include <QRegularExpression>
#include <QSpinBox>
#include <QTime>
#include <QWidget>

#include "tabmodel.h"

#include "../tools/utils.h"
#include "../tools/recurrence.h"
#include "../tools/todolist.h"

class Task;

class TaskDialog : public QDialog
{
    Q_OBJECT

private:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                            ATTRIBUTES                             *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    //Layouts
    QBoxLayout *timeLayout;
    QGridLayout *mainLayout;

    //Title
    QLabel *labelTitle, *labelName, *labelDeadline, *labelReccurence, *labelDuration, *labelParent, *labelPriority;

    //User imputs
    QComboBox *cmbReccurence, *cmbParent;

    QLineEdit *textName, *textDeadline, *textDuration;

    QPushButton *btnSubmit;

    QSpinBox *nudPriority;


    int defineAllSons(Task *task) const;

    //Tools
    Task *task = nullptr;
    ToDoList *toDoList;
    QSet<Task *> *AllSons;

public:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                           CONSTRUCTORS                            *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    //Both for modification and for a new Task has the same constructors
    TaskDialog(ToDoList *tdl, bool addDialog, QWidget *_parent = nullptr);

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PUBLIC METHODS                           *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    //initialize change how the Dialog function
    void initialize(Task * = nullptr);
private slots:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
     *                            SLOTS                            *
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    //depending on the initialization the Close won't work the same
    void addAndClose();
    void updateAndClose();

signals:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
     *                           SIGNALS                           *
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    //Used to refresh the TaskManagement
    void taskAdded(Task *);
    void taskUpdated();
};

#endif // TASKDIALOG_H
