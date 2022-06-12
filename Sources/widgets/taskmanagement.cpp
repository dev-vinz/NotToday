#include "taskmanagement.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                           CONSTRUCTORS                            *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

TaskManagement::TaskManagement(QWidget *_parent) : TabModel(_parent)
{
    //Layout
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

    //Title
    lblTitle = new QLabel("Aperçu des tâches");
    QFont font = lblTitle->font();
    font.setUnderline(1);
    lblTitle->setFont(font);
    topLayout->addWidget(lblTitle);

    //Button
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

    //Header
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

    //layout
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

    //Dialogs
    addTaskDialog = new TaskDialog(&TaskManagement::tdl, true);
    modifyTask = new TaskDialog(&TaskManagement::tdl, false);

    //Connect
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
    //The color oh the button depends on its status

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
            this->tabTaskRadio.push_back(this->tasks[i][j]->getId());//Used to know wich task is linked with what radiobutton
            addNewTask(nb); //Add the space for the task to be displayed
            displayTask(this->tasks[i][j], nb++); //put the values of the tasks is the accorfing space
        }
    }
}

void TaskManagement::initialize()
{
    //Disable the button depending on a task needed to be selected
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

    //Delete and clear everything
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

    //Display everything back
    this->tasks = displayBlock;
    this->displayTasks();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                          PRIVATE METHODS                          *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//Add the space for the task to be displayed
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

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                            SLOTS                            *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void TaskManagement::deleteTask()
{
    if (this->selectedTask == nullptr) return;
    selectedTask->setStatus(TaskStatus::DOING);
    statusButtonPressed(); //Unlock the parents
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

//Used to know wich task to update, delete or change status
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

//Change the status depending on the previous status
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
