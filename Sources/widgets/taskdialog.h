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

    QBoxLayout *timeLayout;
    QGridLayout *mainLayout;

    QLabel *labelTitle, *labelName, *labelDeadline, *labelReccurence, *labelDuration, *labelParent, *labelPriority;

    QComboBox *cmbReccurence, *cmbParent;

    QLineEdit *textName, *textDeadline, *textDuration;

    QPushButton *btnSubmit;

    QSpinBox *nudPriority;

    Task *task = nullptr;
    ToDoList *toDoList;

public:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                           CONSTRUCTORS                            *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    TaskDialog(ToDoList *tdl, bool addDialog, QWidget *_parent = nullptr); //Constructeur pour modifier une tâche

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PUBLIC METHODS                           *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    void initialize(Task * = nullptr);

private slots:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
     *                            SLOTS                            *
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    void addAndClose();
    void updateAndClose();

signals:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
     *                           SIGNALS                           *
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    void taskAdded(Task *);
    void taskUpdated();
};

#endif // TASKDIALOG_H
