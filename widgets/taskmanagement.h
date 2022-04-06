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
public:
    TaskManagement(QWidget *_parent = nullptr);
    void useTask();

    QBoxLayout *topLayout;
    QBoxLayout *mainLayout;
    QBoxLayout *defaultLayout;

    QPushButton *btnAddTask;
    QPushButton *btnRemoveTask;
    QPushButton *btnModifyTask;
    QLabel *lblTitle;

    QGridLayout *boardLayout;

    QLabel *selectLabel;
    QLabel *statusLabel;
    QLabel *nameLabel;
    QLabel *dateLabel;
    QLabel *durationLabel;
    QLabel *progressionLabel;

    QDialog *addTask;
    QDialog *modifyTask;

private:
    void getTasks();


protected:
    void initialize() override;
public slots:
        void openNewWindow();
};

#endif // TASKMANAGEMENT_H
