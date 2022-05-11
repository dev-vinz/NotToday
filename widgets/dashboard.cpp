#include "dashboard.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                           CONSTRUCTORS                            *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

Dashboard::Dashboard(QWidget *_parent) : TabModel(_parent)
{
    this->initialize();

    //initialize list of item of the Tasks
    radSelectTask = new QVector<QRadioButton *>;
    btnStatusTask = new QVector<QPushButton *>;
    lblNameTask = new QVector<QLabel *>;
    lblDateTask = new QVector<QLabel *>;
    lblDurationTask = new QVector<QLabel *>;
    pgbProgressionTask = new QVector<QProgressBar *>;


    //Initialise the Layouts
    mainLayout = new QVBoxLayout(this);
    defaultLayout = new QHBoxLayout(this);
    boardLayout = new QGridLayout(this);

    lblTitle = new QLabel("DashBoard");
    QFont font = lblTitle->font();
    font.setUnderline(1);
    lblTitle->setFont(font);
    lblTitle->setMaximumHeight(20);

    mainLayout->addWidget(lblTitle);

    mainLayout->addLayout(boardLayout);

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


    boardLayout->addWidget(selectLabel, 0, 0);
    boardLayout->addWidget(statusLabel, 0, 1);
    boardLayout->addWidget(nameLabel, 0, 2);
    boardLayout->addWidget(dateLabel, 0, 3);
    boardLayout->addWidget(durationLabel, 0, 4);
    boardLayout->addWidget(progressionLabel, 0, 5);

    tasks.append(createTask());
    tasks.append(createTask());
    tasks.append(createTask());
    tasks.append(createTask());

    //pour chaque tâche on en ajoute une "Vide" puis on la remplace par les bonnes valeurs
    for(int i = 0; i < tasks.size(); i++)
    {
        addNewTask(i);
        displayTask(tasks.at(i), i);
    }

    mainLayout->addLayout(defaultLayout);
    mainLayout->setStretch(0, 1);
    mainLayout->setStretch(1, 9);
    mainLayout->setStretch(2, 1);

    connect(actOpen, &QAction::triggered, this, &Dashboard::addTask);
}

/* * * * * * * * * * * * * * * * * * *\
|*              GETTERS              *|
\* * * * * * * * * * * * * * * * * * */

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

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                         PROTECTED METHODS                         *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Dashboard::displayTask(Task task, int indice) const
{
    switch (task.getStatus()) {
    case TaskStatus::DOING:
        btnStatusTask->at(indice)->setStyleSheet("background: orange;");
        break;
    case TaskStatus::DONE:
        btnStatusTask->at(indice)->setStyleSheet("background: red;");
        break;
    case TaskStatus::OPEN:
        btnStatusTask->at(indice)->setStyleSheet("background: green;");
        break;
    default:
        btnStatusTask->at(indice)->setStyleSheet("background: gray;");
        break;
    }
    lblNameTask->at(indice)->setText(task.getName());
    lblDateTask->at(indice)->setText(Utils::dateToString(task.getDeadline()));
    lblDurationTask->at(indice)->setText(task.getDurationString());
    pgbProgressionTask->at(indice)->setMaximum(100); //VOir comment faire avec la progression
    pgbProgressionTask->at(indice)->setValue(50);
}

void Dashboard::initialize()
{
    this->createActions();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                          PRIVATE METHODS                          *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Dashboard::addNewTask(int i)
{
    radSelectTask->push_back(new QRadioButton(this));
    btnStatusTask->push_back(new QPushButton(this));
    lblNameTask->push_back(new QLabel("NO_NAME", this));
    lblDateTask->push_back(new QLabel("NO_DATE", this));
    lblDurationTask->push_back(new QLabel("NO_DURATION"));
    pgbProgressionTask->push_back(new QProgressBar(this));

    boardLayout->addWidget(radSelectTask->at(i), i + 1, 0);
    boardLayout->addWidget(btnStatusTask->at(i), i + 1, 1);
    boardLayout->addWidget(lblNameTask->at(i), i + 1, 2);
    boardLayout->addWidget(lblDateTask->at(i),i + 1, 3);
    boardLayout->addWidget(lblDurationTask->at(i), i + 1, 4);
    boardLayout->addWidget(pgbProgressionTask->at(i),i + 1, 5);
}

void Dashboard::addTask()
{
    this->tasks.append(createTask());
    addNewTask(this->tasks.size() - 1);
    displayTask(this->tasks.at(this->tasks.size() - 1), this->tasks.size() - 1);
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

void Dashboard::displayTasks()
{
    for(int i = 0; i < tasks.size(); i++)
    {
        displayTask(tasks.at(i), i);
    }
}
