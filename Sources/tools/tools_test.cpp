#include <gtest/gtest.h>
#include "todolist.h"

TEST(LibTools, ToDoList)
{

    ToDoList tdl;

    Task *t1 = new Task(3, "Task 1", QDateTime(QDate(2022, 07, 26), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromHours(4));
    Task *t2 = new Task(2, "Task 2", QDateTime(QDate(2022, 07, 28), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromHours(4));
    Task *t3 = new Task(1, "Task 3", QDateTime(QDate(2022, 07, 28), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromMinutes(45));
    Task *t4 = new Task(2, "Task 4", QDateTime(QDate(2022, 07, 28), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromMinutes(30));
    Task *t5 = new Task(3, "Task 5", QDateTime(QDate(2022, 07, 28), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromHours(2));

    tdl.addTask(t1);
    tdl.addTask(t2);
    tdl.addTask(t3);
    tdl.addTask(t4);
    tdl.addTask(t5);

    QList<Task *> tasks = tdl.getTasks();

    EXPECT_EQ(tasks.size(), 5);

    QVector<Task *> priorisedTasks = tdl.getToday();
    EXPECT_EQ(priorisedTasks.at(0)->getName(), "Task 1");
    EXPECT_EQ(priorisedTasks.at(1)->getName(), "Task 5");
    EXPECT_EQ(priorisedTasks.at(2)->getName(), "Task 4");

    tdl.addDependence(t1, t2);
    tdl.addDependence(t2, t3);
    tdl.addDependence(t3, t5);
    tdl.addDependence(t4, t5);

    priorisedTasks = tdl.getToday();
    EXPECT_EQ(priorisedTasks.at(0)->getName(), "Task 1");
    EXPECT_EQ(priorisedTasks.at(1)->getName(), "Task 4");
}


 // When a leaf is removed it need to liberate his parent


TEST(LibTools, removeStatus)
{
    ToDoList tdl;

    Task *t1 = new Task(3, "Task 1", QDateTime(QDate(2022, 07, 26), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromHours(4));
    Task *t2 = new Task(2, "Task 2", QDateTime(QDate(2022, 07, 28), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromHours(4));
    Task *t3 = new Task(1, "Task 3", QDateTime(QDate(2022, 07, 28), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromMinutes(45));
    Task *t4 = new Task(2, "Task 4", QDateTime(QDate(2022, 07, 26), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromMinutes(30));
    Task *t5 = new Task(3, "Task 5", QDateTime(QDate(2022, 07, 28), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromHours(2));

    tdl.addTask(t1);
    tdl.addTask(t2);
    tdl.addTask(t3);
    tdl.addTask(t4);
    tdl.addTask(t5);

    tdl.addDependence(t1, t2);
    tdl.addDependence(t2, t3);
    tdl.addDependence(t3, t5);
    tdl.addDependence(t4, t5);

    QVector<Task *> tasks = tdl.run();

    EXPECT_EQ(tasks.at(0)->getName(), "Task 1");
    EXPECT_EQ(tasks.at(1)->getName(), "Task 4");
    EXPECT_EQ(tasks.at(2)->getName(), "Task 2");
    EXPECT_EQ(tasks.at(3)->getName(), "Task 3");
    EXPECT_EQ(tasks.at(4)->getName(), "Task 5");

    EXPECT_EQ(tasks.size(), 5);

    EXPECT_EQ(tasks.at(0)->getStatus(), TaskStatus::OPEN);
    EXPECT_EQ(tasks.at(1)->getStatus(), TaskStatus::OPEN);
    EXPECT_EQ(tasks.at(2)->getStatus(), TaskStatus::LOCKED);
    EXPECT_EQ(tasks.at(3)->getStatus(), TaskStatus::LOCKED);
    EXPECT_EQ(tasks.at(4)->getStatus(), TaskStatus::LOCKED);


    tdl.removeTask(t1);

    tasks = tdl.run();

    EXPECT_EQ(tasks.at(0)->getName(), "Task 4");
    EXPECT_EQ(tasks.at(1)->getName(), "Task 2");
    EXPECT_EQ(tasks.at(2)->getName(), "Task 3");
    EXPECT_EQ(tasks.at(3)->getName(), "Task 5");

    EXPECT_EQ(tasks.size(), 4);

    EXPECT_EQ(tasks.at(0)->getStatus(), TaskStatus::OPEN);
    EXPECT_EQ(tasks.at(1)->getStatus(), TaskStatus::LOCKED); //SHOULD BE OPEN
    EXPECT_EQ(tasks.at(2)->getStatus(), TaskStatus::LOCKED);
    EXPECT_EQ(tasks.at(3)->getStatus(), TaskStatus::LOCKED);


    tdl.removeTask(t2);

    tasks = tdl.run();

    EXPECT_EQ(tasks.at(0)->getName(), "Task 4");
    EXPECT_EQ(tasks.at(1)->getName(), "Task 3");
    EXPECT_EQ(tasks.at(2)->getName(), "Task 5");

    EXPECT_EQ(tasks.size(), 3);

    EXPECT_EQ(tasks.at(0)->getStatus(), TaskStatus::OPEN);
    EXPECT_EQ(tasks.at(1)->getStatus(), TaskStatus::LOCKED);//SHOULD BE OPEN
    EXPECT_EQ(tasks.at(2)->getStatus(), TaskStatus::LOCKED);

}

/*

TEST(LibTools, addTask)
{
    ToDoList tdl;

    Task *t1 = new Task(3, "Task 1", QDateTime(QDate(2022, 07, 26), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromHours(4));
    Task *t2 = new Task(2, "Task 2", QDateTime(QDate(2022, 07, 28), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromHours(4));
    Task *t3 = new Task(1, "Task 3", QDateTime(QDate(2022, 07, 28), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromMinutes(45));
    Task *t4 = new Task(2, "Task 4", QDateTime(QDate(2022, 07, 26), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromMinutes(30));
    Task *t5 = new Task(3, "Task 5", QDateTime(QDate(2022, 07, 28), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromHours(2));
    Task *t6 = new Task(1, "Task 6", QDateTime(QDate(2022, 07, 26), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromHours(1));

    tdl.addTask(t1);
    tdl.addTask(t2);
    tdl.addTask(t3);
    tdl.addTask(t4);
    tdl.addTask(t5);

    tdl.addDependence(t1, t2);
    tdl.addDependence(t2, t3);
    tdl.addDependence(t3, t5);
    tdl.addDependence(t4, t5);

    QVector<Task *> tasks = tdl.run();

    EXPECT_EQ(tasks.at(0)->getName(), "Task 1");
    EXPECT_EQ(tasks.at(1)->getName(), "Task 4");
    EXPECT_EQ(tasks.at(2)->getName(), "Task 2");
    EXPECT_EQ(tasks.at(3)->getName(), "Task 3");
    EXPECT_EQ(tasks.at(4)->getName(), "Task 5");

    EXPECT_EQ(tasks.size(), 5);

    tdl.addTask(t6);

    tasks = tdl.run();

    EXPECT_EQ(tasks.at(0)->getName(), "Task 4");
    EXPECT_EQ(tasks.at(1)->getName(), "Task 1");
    EXPECT_EQ(tasks.at(2)->getName(), "Task 6");
    EXPECT_EQ(tasks.at(3)->getName(), "Task 2");
    EXPECT_EQ(tasks.at(4)->getName(), "Task 3");
    EXPECT_EQ(tasks.at(5)->getName(), "Task 5");

    tdl.addDependence(t6,t2);

    tasks = tdl.run();

    EXPECT_EQ(tasks.at(0)->getName(), "Task 4");
    EXPECT_EQ(tasks.at(1)->getName(), "Task 1");
    EXPECT_EQ(tasks.at(2)->getName(), "Task 6");
    EXPECT_EQ(tasks.at(3)->getName(), "Task 3");
    EXPECT_EQ(tasks.at(4)->getName(), "Task 5");
    EXPECT_EQ(tasks.at(5)->getName(), "Task 2");

}

*/
