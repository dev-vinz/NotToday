#ifndef TASKMANAGEMENT_H
#define TASKMANAGEMENT_H

#include <QObject>
#include <QWidget>

#include "tabmodel.h"

class TaskManagement : public TabModel
{
    Q_OBJECT
public:
    TaskManagement(QWidget *_parent = nullptr);

protected:
    //void displayTasks() const override;
    void initialize() override;
};

#endif // TASKMANAGEMENT_H
