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

    void createActions();
    void displayTask(Task task, int indice);
    void displayTasks();
    void addTask();
    void addNewTask(int i);
public:
    Dashboard(QWidget *_parent = nullptr);

    QAction *getNewAction() const;
    QAction *getOpenAction() const;
    QAction *getSaveAction() const;
    QBoxLayout *mainLayout;
    QBoxLayout *defaultLayout;

    QLabel *lblTitle;
    QGridLayout *boardLayout;
    QLabel *selectLabel;
    QLabel *statusLabel;
    QLabel *nameLabel;
    QLabel *dateLabel;
    QLabel *durationLabel;
    QLabel *progressionLabel;

    QBoxLayout *taskLayout;

    QVector<QRadioButton *> *radSelectTask;
    QVector<QPushButton *> *btnStatusTask;
    QVector<QLabel *> *lblNameTask;
    QVector<QLabel *> *lblDateTask;
    QVector<QLabel *> *lblDurationTask;
    QVector<QProgressBar *> *pgbProgressionTask;


protected:
    void initialize() override;
};

#endif // DASHBOARD_H
