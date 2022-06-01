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

    ToDoList *toDoList;

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                          PRIVATE METHODS                          *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    void initialize();

public:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
    |*                           CONSTRUCTORS                            *|
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    TaskDialog(QWidget *_parent= nullptr); //Constructeur pour créer une nouvelle tâche
    TaskDialog(Task task, QWidget *_parent = nullptr); //Constructeur pour modifier une tâche

private slots:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
     *                            SLOTS                            *
    \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    void saveAndClose();
};

#endif // TASKDIALOG_H
