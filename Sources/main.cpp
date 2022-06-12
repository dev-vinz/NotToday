#include <QApplication>

#include "widgets/mainwindow.h"
#include "tools/todolist.h"
#include "tools/timespan.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    a.exec();

    return 0;
}
