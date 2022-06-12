#include "taskmanagement.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                           CONSTRUCTORS                            *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

TaskManagement::TaskManagement(QWidget *_parent) : TabModel(_parent)
{
    mainLayout = new QVBoxLayout(this);
    topLayout = new QHBoxLayout();
    boardLayout = new QGridLayout();
    defaultLayout = new QHBoxLayout();
    mainLayout->addLayout(topLayout);

    // initialize list of item of the Tasks
    radSelectTask = new QVector<QRadioButton *>;
    btnStatusTask = new QVector<QPushButton *>;
    lblNameTask = new QVector<QLabel *>;
    lblDateTask = new QVector<QLabel *>;
    lblDurationTask = new QVector<QLabel *>;
    pgbProgressionTask = new QVector<QProgressBar *>;

    lblTitle = new QLabel("Aperçu des tâches");
    QFont font = lblTitle->font();
    font.setUnderline(1);
    lblTitle->setFont(font);
    topLayout->addWidget(lblTitle);

    btnAddTask = new QPushButton("Ajouter une Tâche", this);
    btnAddTask->setGeometry(500, 50, 150, 50);
    topLayout->addWidget(btnAddTask);

    btnRemoveTask = new QPushButton("Supprimer Tâche", this);
    btnRemoveTask->setGeometry(600, 50, 150, 50);
    topLayout->addWidget(btnRemoveTask);

    btnModifyTask = new QPushButton("Modifier Tâche", this);
    btnModifyTask->setGeometry(700, 50, 150, 50);
    topLayout->addWidget(btnModifyTask);

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

    mainLayout->addLayout(defaultLayout);
    mainLayout->setStretch(0, 1);
    mainLayout->setStretch(1, 9);
    mainLayout->setStretch(2, 1);

    addTaskDialog = new TaskDialog(&TaskManagement::tdl, true);
    modifyTask = new TaskDialog(&TaskManagement::tdl, false);

    connect(btnAddTask, &QPushButton::clicked, this, &TaskManagement::openNewWindow);
    connect(btnModifyTask, &QPushButton::clicked, this, &TaskManagement::openNewWindow);
    connect(btnRemoveTask, &QPushButton::clicked, this, &TaskManagement::deleteTask);

    connect(addTaskDialog, &TaskDialog::taskAdded, this, &TaskManagement::refresh);
    connect(modifyTask, &TaskDialog::taskUpdated, this, &TaskManagement::refresh);
}



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                         PROTECTED METHODS                         *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void TaskManagement::displayTask(Task *task, int indice) const
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

    double pgValue = 0;
    int nbSons = defineAllSons(task);
    double time = defineAllTime(task);

    if(nbSons > 0)
    {
        pgValue = definePG(task, time);
    }
        if (task->getStatus() == TaskStatus::DONE)
        {
            pgValue = 100;
        }

    pgbProgressionTask->at(indice)->setValue(pgValue);
}



void TaskManagement::displayTasks()
{
    int nb = 0;

    for (int i = 0; i < this->tasks.length(); i++)
    {
        for (int j = 0; j < this->tasks[i].length(); j++)
        {
            this->tabTaskRadio.push_back(this->tasks[i][j]->getId());
            addNewTask(nb);
            displayTask(this->tasks[i][j], nb++);
        }
    }
}

void TaskManagement::initialize()
{
    btnModifyTask->setEnabled(false);
    btnRemoveTask->setEnabled(false);

    QVector<Task *> orderedTasks = this->tdl.run();
    QVector<QVector<Task *>> displayBlock;

    QVector<Task *> tempTab;

    foreach (Task *task, orderedTasks)
    {
        QList<Task *> sons = this->tdl.getSonsOf(task);

        // If task has at least one son, we skip it
        if (sons.size() > 0) continue;

        // Certification, we start from leaf
        Task *currentTask = task;

        while (currentTask->getParents().size() > 0)
        {
            tempTab.push_front(currentTask);

            // Assumption : Has only one parent
            currentTask = currentTask->getParents().at(0);
        }

        // Push last one
        tempTab.push_front(currentTask);

        // Add to block
        displayBlock.push_back(tempTab);

        // Erase tempTab
        tempTab.erase(tempTab.begin(), tempTab.end());
    }

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

    this->tasks = displayBlock;
    this->displayTasks();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                          PRIVATE METHODS                          *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void TaskManagement::addNewTask(int i)
{
    QRadioButton *btn = new QRadioButton(this);
    QPushButton *statusButton = new QPushButton(this);
    statusButton->setEnabled(false);

    connect(btn, &QRadioButton::toggled, this, &TaskManagement::radioButtonClicked);
    connect(statusButton, &QPushButton::pressed, this, &TaskManagement::statusButtonPressed);

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

int TaskManagement::defineAllTime(Task *task) const
{
    QList<Task *> sons = TaskManagement::tdl.getSonsOf(task);
    int value = task->getDuration().totalMinutes();
    if(sons.size()<=0)
    {
        return value;
    }

    foreach(Task * son, sons)
    {
        value += defineAllTime(son);
    }
    return value;
}

int TaskManagement::defineAllSons(Task *task) const
{
    QList<Task *> sons = TaskManagement::tdl.getSonsOf(task);
    int value = 0;
    if(sons.size()<=0)
    {
        return 0;
    }

    foreach(Task * son, sons)
    {
        value += 1 + defineAllSons(son);
    }
    return value;
}

double TaskManagement::definePG(Task *task, int time) const
{
    QList<Task *> sons = TaskManagement::tdl.getSonsOf(task);
    double value = 0;

    if (task->getStatus() == TaskStatus::DONE)
    {
        value += 100.0 / time*task->getDuration().totalMinutes();
    }

    if(sons.size()<=0)
    {
        return value;
    }

    foreach(Task * son, sons)
    {
        value += definePG(son,time);
    }
    return value;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                            SLOTS                            *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void TaskManagement::deleteTask()
{
    if (this->selectedTask == nullptr) return;
    selectedTask->setStatus(TaskStatus::DOING);
    statusButtonPressed(); //Pour libérer les parents
    this->tdl.removeTask(this->selectedTask);
    this->selectedTask = nullptr;

    refresh();
}

void TaskManagement::openNewWindow()
{
    QObject *emmetteur = sender();

    if (emmetteur == btnModifyTask)
    {
        if (this->selectedTask == nullptr) return;
        modifyTask->initialize(this->selectedTask);
        modifyTask->show();
    }
    else
    {
        addTaskDialog->initialize();
        addTaskDialog->show();
    }
}

void TaskManagement::refresh()
{
    this->initialize();
}

void TaskManagement::radioButtonClicked(bool isChecked)
{
    if (isChecked)
    {
        this->btnModifyTask->setEnabled(true);
        this->btnRemoveTask->setEnabled(true);

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

void TaskManagement::statusButtonPressed()
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
            QList<Task *> otherSons = TaskManagement::tdl.getSonsOf(directParent);

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
