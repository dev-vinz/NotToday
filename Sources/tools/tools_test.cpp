#include <gtest/gtest.h>
#include "todolist.h"

TEST(LibTools, ToDoList)
{
    ToDoList tdl();

    Task *t1 = new Task(TaskStatus::OPEN, 3, "Task 1", QDateTime(QDate(2022, 04, 26), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromHours(4));
    Task *t2 = new Task(TaskStatus::OPEN, 1, "Task 2", QDateTime(QDate(2022, 04, 28), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromHours(4));
    Task *t3 = new Task(TaskStatus::OPEN, 1, "Task 3", QDateTime(QDate(2022, 04, 28), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromMinutes(45));
    Task *t4 = new Task(TaskStatus::OPEN, 2, "Task 4", QDateTime(QDate(2022, 04, 28), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromMinutes(30));
    Task *t5 = new Task(TaskStatus::OPEN, 3, "Task 5", QDateTime(QDate(2022, 04, 28), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromHours(2));

    tdl.addTask(t1);
    tdl.addTask(t2);
    tdl.addTask(t3);
    tdl.addTask(t4);
    tdl.addTask(t5);

    QList<Task *> tasks = tdl.getTasks();

    EXPECT_EQ(tasks.length(), 5);

    QVector<Task *> priorisedTasks = tdl.getToday();
    EXPECT_EQ(priorisedTasks[0]->getName(), "Task 1");
    EXPECT_EQ(priorisedTasks[1]->getName(), "Task ");
    EXPECT_EQ(priorisedTasks[2]->getName(), "Task ");
    EXPECT_EQ(priorisedTasks[3]->getName(), "Task ");
    EXPECT_EQ(priorisedTasks[4]->getName(), "Task ");

    tdl.addDependence(t1, t2);
    tdl.addDependence(t2, t3);
    tdl.addDependence(t3, t5);
    tdl.addDependence(t4, t5);

    priorisedTasks = tdl.getToday();
    EXPECT_EQ(priorisedTasks[0]->getName(), "Task 1");
    EXPECT_EQ(priorisedTasks[1]->getName(), "Task ");
    EXPECT_EQ(priorisedTasks[2]->getName(), "Task ");
    EXPECT_EQ(priorisedTasks[3]->getName(), "Task ");
    EXPECT_EQ(priorisedTasks[4]->getName(), "Task ");


}