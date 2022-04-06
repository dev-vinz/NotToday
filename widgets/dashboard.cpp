#include "dashboard.h"

Dashboard::Dashboard(QWidget *_parent) : TabModel(_parent)
{
    this->initialize();
    mainLayout = new QVBoxLayout(this);
    topLayout = new QHBoxLayout(this);

    boardLayout = new QGridLayout(this);
    //boardLayout = new QGridLayout(this);
    taskLayout = new QGridLayout(this);

    mainLayout->addLayout(topLayout);
    /*QSpacerItem *spacer = new QSpacerItem(this->width(),10);
    mainLayout->addSpacerItem(spacer);*/
    mainLayout->addLayout(boardLayout);


    lblTitle = new QLabel("DashBoard");
    lblTitle->setMaximumHeight(20);

    QFont font = lblTitle->font();
    font.setUnderline(1);
    lblTitle->setFont(font);
    topLayout->addWidget(lblTitle);

    selectLabel = new QLabel("Selecteur");
    selectLabel->setStyleSheet("background: rgba(31,144,186,255); border: 2px solid black;");
    selectLabel->setMaximumHeight(40);
    statusLabel= new QLabel("Status");
    statusLabel->setStyleSheet("background: rgba(31,144,186,255); border: 2px solid black;");
    nameLabel= new QLabel("Name");
    nameLabel->setStyleSheet("background: rgba(31,144,186,255); border: 2px solid black;");
    dateLabel= new QLabel("Date");
    dateLabel->setStyleSheet("background: rgba(31,144,186,255); border: 2px solid black;");
    durationLabel= new QLabel("Duration");
    durationLabel->setStyleSheet("background: rgba(31,144,186,255); border: 2px solid black;");
    progressionLabel= new QLabel("Progression");
    progressionLabel->setStyleSheet("background: rgba(31,144,186,255); border: 2px solid black;");



    boardLayout->addWidget(selectLabel,0,0);
    boardLayout->addWidget(statusLabel,0,1);
    boardLayout->addWidget(nameLabel,0,2);
    boardLayout->addWidget(dateLabel,0,3);
    boardLayout->addWidget(durationLabel,0,4);
    boardLayout->addWidget(progressionLabel,0,5);
//        boardLayout->addWidget(selectLabel);
//        boardLayout->addWidget(statusLabel);
//        boardLayout->addWidget(nameLabel);
//        boardLayout->addWidget(dateLabel);
//        boardLayout->addWidget(durationLabel);
//        boardLayout->addWidget(progressionLabel);

    tasks.append(createTask());
    tasks.append(createTask());
    tasks.append(createTask());
    tasks.append(createTask());

    //foreach tasks in the list we create a new Label
    for(int i = 0; i<tasks.size();i++)
    {
        radSelectTask = new QRadioButton(this);
        btnStatusTask = new QPushButton(this);
        lblNameTask = new QLabel("NO_NAME",this);
        lblDateTask = new QLabel("NO_DATE",this);
        lblDurationTask = new QLabel("NO_DURATION");
        pgbProgressionTask = new QProgressBar(this);

        boardLayout->addWidget(radSelectTask,i+1,0);
        boardLayout->addWidget(btnStatusTask,i+1,1);
        boardLayout->addWidget(lblNameTask,i+1,2);
        boardLayout->addWidget(lblDateTask,i+1,3);
        boardLayout->addWidget(lblDurationTask,i+1,4);
        boardLayout->addWidget(pgbProgressionTask,i+1,5);
//        taskLayout->addWidget(radSelectTask);
//        taskLayout->addWidget(btnStatusTask);
//        taskLayout->addWidget(lblNameTask);
//        taskLayout->addWidget(lblDateTask);
//        taskLayout->addWidget(lblDurationTask);
//        taskLayout->addWidget(pgbProgressionTask);
        displayTask(tasks.at(i));
    }


}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                           PRIVATE                           *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Task Dashboard::createTask()
{
    TaskStatus status = TaskStatus::DOING;
    int prio = 34;
    QString name = "Tester le CRUD";
    QDateTime deadline =QDateTime(QDate(2024,12,2), QTime(0,0,0));
    QDateTime start =QDateTime(QDate(2023,12,2), QTime(0,0,0));
    Task::Recurrence recu = Task::Recurrence::everyTwoWeek;
    QDateTime dura = QDateTime(QDate(0,0,0), QTime(15,15,15));
    return Task(status,prio, name, deadline,start,recu,dura);
}
void Dashboard::displayTask(Task task)
{
    switch (task.status) {
    case TaskStatus::DOING:
        btnStatusTask->setStyleSheet("background: orange;");
        break;
    case TaskStatus::DONE:
        btnStatusTask->setStyleSheet("background: red;");
        break;
    case TaskStatus::OPEN:
        btnStatusTask->setStyleSheet("background: green;");
        break;
    default:
        btnStatusTask->setStyleSheet("background: gray;");
        break;
    }
    lblNameTask->setText(task.name);
    lblDateTask->setText(task.DateToString(task.deadline));
    lblDurationTask->setText(task.DurationToString());
    pgbProgressionTask->setMaximum(100); //VOir comment faire avec la progression
    pgbProgressionTask->setValue(50);
}
void Dashboard::displayTasks()
{
    foreach(Task task, tasks)
    {
        displayTask(task);
    }
}

void Dashboard::createActions()
{
    this->actSave = new QAction(tr("&Save"));
    this->actSave->setShortcut(tr("CTRL+S"));
    this->actSave->setStatusTip(tr("Save file in your computer"));

    this->actOpen = new QAction(tr("&Open"));
    this->actOpen->setShortcut(tr("CTRL+O"));
    this->actOpen->setStatusTip(tr("Open file from your computer"));

    this->actNew = new QAction(tr("&New"));
    this->actNew->setShortcut(tr("CTRL+N"));
    this->actNew->setStatusTip(tr("Create a new blank file"));
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                          PROTECTED                          *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


void Dashboard::initialize()
{
    this->createActions();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                           PUBLIC                            *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

QAction *Dashboard::getNewAction() const
{
    return this->actNew;
}

QAction *Dashboard::getOpenAction() const
{
    return this->actOpen;
}

QAction *Dashboard::getSaveAction() const
{
    return this->actSave;
}
