#ifndef TABMODEL_H
#define TABMODEL_H

#include <QObject>
#include <QTabBar>
#include <QWidget>

class TabModel : public QTabBar
{
    Q_OBJECT

public:
    TabModel(QWidget *_parent);

protected:
    //void virtual displayTasks() const = 0;
    void virtual initialize() = 0;
};

#endif // TABMODEL_H
