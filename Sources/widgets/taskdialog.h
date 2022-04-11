#ifndef TASKDIALOG_H
#define TASKDIALOG_H

#include <QDialog>
#include <QObject>
#include <QWidget>

class TaskDialog : public QDialog
{
    Q_OBJECT
public:
    TaskDialog(QWidget *_parent = nullptr);
};

#endif // TASKDIALOG_H
