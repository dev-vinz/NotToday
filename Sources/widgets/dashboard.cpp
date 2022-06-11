#include "dashboard.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                           CONSTRUCTORS                            *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

Dashboard::Dashboard(QWidget *_parent) : TabModel(_parent)
{
    // initialize list of item of the Tasks
    radSelectTask = new QVector<QRadioButton *>;
    btnStatusTask = new QVector<QPushButton *>;
    lblNameTask = new QVector<QLabel *>;
    lblDateTask = new QVector<QLabel *>;
    lblDurationTask = new QVector<QLabel *>;
    pgbProgressionTask = new QVector<QProgressBar *>;

    // Initialise the Layouts
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
    statusLabel = new QLabel("Status");
    statusLabel->setStyleSheet("background: rgba(31,144,186,255); border: 2px solid black;");
    nameLabel = new QLabel("Name");
    nameLabel->setStyleSheet("background: rgba(31,144,186,255); border: 2px solid black;");
    dateLabel = new QLabel("Date");
    dateLabel->setStyleSheet("background: rgba(31,144,186,255); border: 2px solid black;");
    durationLabel = new QLabel("Duration");
    durationLabel->setStyleSheet("background: rgba(31,144,186,255); border: 2px solid black;");
    progressionLabel = new QLabel("Progression");
    progressionLabel->setStyleSheet("background: rgba(31,144,186,255); border: 2px solid black;");

    boardLayout->addWidget(selectLabel, 0, 0);
    boardLayout->addWidget(statusLabel, 0, 1);
    boardLayout->addWidget(nameLabel, 0, 2);
    boardLayout->addWidget(dateLabel, 0, 3);
    boardLayout->addWidget(durationLabel, 0, 4);
    boardLayout->addWidget(progressionLabel, 0, 5);

    Task *t1 = new Task(3, "Task 1", QDateTime(QDate(2022, 06, 28), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromHours(4));
    Task *t2 = new Task(1, "Task 2", QDateTime(QDate(2022, 06, 28), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromHours(4));
    Task *t3 = new Task(1, "Task 3", QDateTime(QDate(2022, 06, 28), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromMinutes(45));
    Task *t4 = new Task(2, "Task 4", QDateTime(QDate(2022, 06, 28), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromMinutes(30));
    Task *t5 = new Task(3, "Task 5", QDateTime(QDate(2022, 06, 28), QTime(15, 0)), QDateTime::currentDateTime(), TimeSpan::fromHours(2));

    tdl.addTask(t1);
    tdl.addTask(t2);
    tdl.addTask(t3);
    tdl.addTask(t4);
    tdl.addTask(t5);

    tdl.addDependence(t1, t2);
    tdl.addDependence(t2, t3);
    tdl.addDependence(t3, t5);
    tdl.addDependence(t4, t5);

    // pour chaque tâche on en ajoute une "Vide" puis on la remplace par les bonnes valeurs

    this->initialize();

    mainLayout->addLayout(defaultLayout);
    mainLayout->setStretch(0, 1);
    mainLayout->setStretch(1, 9);
    mainLayout->setStretch(2, 1);

    this->createActions();
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

void Dashboard::displayTask(Task *task, int indice) const
{
    switch (task->getStatus())
    {
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

    lblNameTask->at(indice)->setText(task->getName());
    lblDateTask->at(indice)->setText(Utils::dateToString(task->getDeadline()));
    lblDurationTask->at(indice)->setText(task->getDuration().toString());
    pgbProgressionTask->at(indice)->setMaximum(100);

    int pgValue = 0;

    QList<Task *> sons = Dashboard::tdl.getSonsOf(task);

    if (sons.size() < 1)
    {
        if (task->getStatus() == TaskStatus::DONE)
        {
            pgValue = 100;
        }
    }
    else
    {
        int nbSons = sons.count() + 1;

        foreach (Task *son, sons)
        {
            if (son->getStatus() == TaskStatus::DONE)
            {
                pgValue += 100 / nbSons;
            }
        }
    }

    pgbProgressionTask->at(indice)->setValue(pgValue);
}

void Dashboard::displayTasks()
{
    for (int i = 0; i < Dashboard::tdl.getToday().size(); i++)
    {
        this->tabTaskRadio.push_back(this->tasks[i]->getId());
        addNewTask(i);
        displayTask(Dashboard::tdl.getToday().at(i), i);
    }
}

void Dashboard::initialize()
{
    foreach (QRadioButton *radio, *radSelectTask)
    {
        delete radio;
    }

    foreach (QPushButton *btn, *btnStatusTask)
    {
        delete btn;
    }

    foreach (QLabel *label, *lblNameTask)
    {
        delete label;
    }

    foreach (QLabel *label, *lblDateTask)
    {
        delete label;
    }

    foreach (QLabel *label, *lblDurationTask)
    {
        delete label;
    }

    foreach (QProgressBar *bar, *pgbProgressionTask)
    {
        delete bar;
    }

    radSelectTask->clear();
    btnStatusTask->clear();
    lblNameTask->clear();
    lblDateTask->clear();
    lblDurationTask->clear();
    pgbProgressionTask->clear();

    tabTaskRadio.clear();

    this->tasks = Dashboard::tdl.getToday();

    this->displayTasks();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                          PRIVATE METHODS                          *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Dashboard::addNewTask(int i)
{
    QRadioButton *btn = new QRadioButton(this);
    QPushButton *statusButton = new QPushButton(this);
    statusButton->setEnabled(false);

    connect(btn, &QRadioButton::toggled, this, &Dashboard::radioButtonClicked);
    connect(statusButton, &QPushButton::pressed, this, &Dashboard::statusButtonPressed);

    radSelectTask->push_back(btn);
    btnStatusTask->push_back(statusButton);
    lblNameTask->push_back(new QLabel("NO_NAME", this));
    lblDateTask->push_back(new QLabel("NO_DATE", this));
    lblDurationTask->push_back(new QLabel("NO_DURATION"));
    pgbProgressionTask->push_back(new QProgressBar(this));

    boardLayout->addWidget(radSelectTask->at(i), i + 1, 0);
    boardLayout->addWidget(btnStatusTask->at(i), i + 1, 1);
    boardLayout->addWidget(lblNameTask->at(i), i + 1, 2);
    boardLayout->addWidget(lblDateTask->at(i), i + 1, 3);
    boardLayout->addWidget(lblDurationTask->at(i), i + 1, 4);
    boardLayout->addWidget(pgbProgressionTask->at(i), i + 1, 5);
}

void Dashboard::createActions()
{
    // TODO : Move ailleurs
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
 *                            SLOTS                            *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
void Dashboard::newTaskAdded(Task *task)
{
    QMessageBox::information(NULL, task->getName(), "Tâche ajoutée depuis la boîte modal, ntr");

    addNewTask(Dashboard::tdl.getToday().size() - 1);
    QMessageBox::information(NULL, task->getName(), "Tâche ajoutée depuis la boîte modal, ntr");
    displayTask(*task, Dashboard::tdl.getToday().size() - 1);
}
*/

void Dashboard::refresh()
{
    this->initialize();
}


void Dashboard::radioButtonClicked(bool isChecked)
{
    if (isChecked)
    {
        // Récupérer l'id du select
        int id = 0;

        for (int k = 0; k < radSelectTask->size(); k++)
        {
            if (radSelectTask->at(k)->isChecked()) id = k;
        }

        this->selectedTask = this->tdl.getTask(this->tabTaskRadio.at(id));

        QList<Task *> sons = this->tdl.getSonsOf(this->selectedTask);

        int nbSonsUndone = 0;

        foreach (Task *son, sons)
        {
            if (son->getStatus() != TaskStatus::DONE) nbSonsUndone++;
        }

        if (nbSonsUndone < 1) btnStatusTask->at(id)->setEnabled(true);
    }
}

void Dashboard::statusButtonPressed()
{
    TaskStatus status = this->selectedTask->getStatus();

    if (status == TaskStatus::OPEN)
    {
        this->selectedTask->setStatus(TaskStatus::DOING);
    }
    else if (status == TaskStatus::DOING)
    {
        this->selectedTask->setStatus(TaskStatus::DONE);

        if (this->selectedTask->getParents().size() > 0)
        {
            Task *directParent = this->selectedTask->getParents().at(0);
            QList<Task *> otherSons = Dashboard::tdl.getSonsOf(directParent);

            int nbUndone = 0;

            foreach (Task *son, otherSons)
            {
                if (son->getStatus() != TaskStatus::DONE) nbUndone++;
            }

            if (nbUndone < 1) directParent->setStatus(TaskStatus::OPEN);
        }
    }

    this->refresh();
}
