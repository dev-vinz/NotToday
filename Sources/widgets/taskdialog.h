#ifndef TASKDIALOG_H
#define TASKDIALOG_H

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QTime>
#include <QGridLayout>
#include <QLineEdit>
#include <QRegularExpression>
#include <QMessageBox>
#include "../Sources/tools/utils.h"
#include "../Sources/tools/recurrence.h"
#include "../Sources/tools/todolist.h"
#include "tabmodel.h"

class Task;
class TaskDialog : public QDialog
{
    Q_OBJECT
public:
    TaskDialog(QWidget *_parent= nullptr); //Constructeur pour créer une nouvelle tâche
    TaskDialog(Task task, QWidget *_parent = nullptr); //Constructeur pour modifier une tâche
private:
    void initialize();


private:
    QLabel *labelTitle;
    QLabel *labelName;
    QLabel *labelDeadline;
    QLabel *labelReccurence;
    QLabel *labelDuration;
    QLabel *labelParent; //IS SON of
    QLabel *labelPriority;

    QLineEdit *textName;
    QLineEdit *textDeadline;
    QComboBox *cmbReccurence;
    QLineEdit *textDuration;
    QComboBox *cmbParent;
    QSpinBox *nudPriority;

    QGridLayout *mainLayout;
    QBoxLayout *timeLayout;


    QPushButton *btnSubmit;


    ToDoList *toDoList;

private slots:
    void saveAndClose();
};

#endif // TASKDIALOG_H
