#include <QApplication>

#include "widgets/mainwindow.h"
#include "tools/todolist.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
    */

    Task *t1 = new Task(TaskStatus::OPEN, 3, "Task 1", QDateTime(QDate(2022, 04, 15), QTime(15, 0)), QDateTime::currentDateTime());
    Task *t2 = new Task(TaskStatus::OPEN, 1, "Task 2", QDateTime(QDate(2022, 04, 14), QTime(15, 0)), QDateTime::currentDateTime());
    Task *t3 = new Task(TaskStatus::OPEN, 1, "Task 3", QDateTime(QDate(2022, 04, 14), QTime(15, 0)), QDateTime::currentDateTime());
    Task *t4 = new Task(TaskStatus::OPEN, 2, "Task 4", QDateTime(QDate(2022, 04, 14), QTime(15, 0)), QDateTime::currentDateTime());
    Task *t5 = new Task(TaskStatus::OPEN, 3, "Task 5", QDateTime(QDate(2022, 04, 14), QTime(15, 0)), QDateTime::currentDateTime());

    ToDoList tdl;

    tdl.addTask(t1);
    tdl.addTask(t2);
    tdl.addTask(t3);
    tdl.addTask(t4);
    tdl.addTask(t5);

    tdl.addDependence(t1, t2);
    tdl.addDependence(t2, t3);
    tdl.addDependence(t3, t5);
    tdl.addDependence(t4, t5);

    QVector<Task *> v1 = tdl.run();
    QVector<Task *> v2 = tdl.run();


    foreach (const Task *task, v1)
    {
        cout << task->getName().toStdString();
    }

    cout << endl;

    cout << "Taille second tableau : " << v2.size() << endl;

    return 0;
}
