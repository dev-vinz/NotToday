QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    tools/task.cpp \
    tools/todolist.cpp \
    widgets//mainwindow.cpp \
    widgets/dashboard.cpp \
    widgets/tabmodel.cpp \
    widgets/tabwidget.cpp \
    widgets/taskdialog.cpp \
    widgets/taskmanagement.cpp

HEADERS += \
    tools/task.h \
    tools/taskstatus.h \
    tools/todolist.h \
    widgets//mainwindow.h \
    widgets/dashboard.h \
    widgets/tabmodel.h \
    widgets/tabwidget.h \
    widgets/taskdialog.h \
    widgets/taskmanagement.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
