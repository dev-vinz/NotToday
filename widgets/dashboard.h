#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QAction>
#include <QFile>
#include <QObject>
#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QProgressBar>
#include <QRadioButton>
#include <QLabel>

#include "tabmodel.h"

class Dashboard : public TabModel
{
    Q_OBJECT

private:
    QAction *actSave, *actOpen, *actNew;
    QFile file;
    QVector<Task> tasks;
    void createActions();
    Task createTask();
    void displayTask(Task task);
    void displayTasks();

public:
    Dashboard(QWidget *_parent = nullptr);

    QAction *getNewAction() const;
    QAction *getOpenAction() const;
    QAction *getSaveAction() const;
    QBoxLayout *mainLayout;

    QBoxLayout *topLayout;
    QLabel *lblTitle;
    QGridLayout *boardLayout;
    QLabel *selectLabel;
    QLabel *statusLabel;
    QLabel *nameLabel;
    QLabel *dateLabel;
    QLabel *durationLabel;
    QLabel *progressionLabel;

    QGridLayout *taskLayout;
    QRadioButton *radSelectTask;
    QPushButton *btnStatusTask;
    QLabel *lblNameTask;
    QLabel *lblDateTask;
    QLabel *lblDurationTask;
    QProgressBar *pgbProgressionTask;


protected:
    //void displayTasks() const override;
    void initialize() override;
};

#endif // DASHBOARD_H
