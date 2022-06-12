#include "taskdialog.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                           CONSTRUCTORS                            *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//Both update and add have the same constructor, initialize() determine how it will work
TaskDialog::TaskDialog(ToDoList *tdl, bool addDialog, QWidget *_parent) : QDialog(_parent), toDoList(tdl)
{
    mainLayout = new QGridLayout(this);

    //Title
    labelTitle = new QLabel("Create New Task");
    QFont font = labelTitle->font();
    font.setUnderline(1);
    labelTitle->setFont(font);
    labelTitle->setMaximumHeight(20);

    mainLayout->addWidget(labelTitle);

    //Labels
    labelName = new QLabel("Task's Name");
    mainLayout->addWidget(labelName, 1, 0);

    labelDeadline = new QLabel("Deadline");
    mainLayout->addWidget(labelDeadline, 1, 1);

    labelReccurence = new QLabel("Reccurence");
    mainLayout->addWidget(labelReccurence, 3, 0);

    labelDuration = new QLabel("Duration");
    mainLayout->addWidget(labelDuration, 3, 1);

    labelParent = new QLabel("Is the son of");
    mainLayout->addWidget(labelParent, 5, 0); // IS SON of

    labelPriority = new QLabel("Priority");
    mainLayout->addWidget(labelPriority, 5, 1);

    //Submit
    btnSubmit = new QPushButton("Submit", this);
    mainLayout->addWidget(btnSubmit, 7, 1);

    //user inputs
    textName = new QLineEdit("", this);
    mainLayout->addWidget(textName, 2, 0);

    textDeadline = new QLineEdit("", this);
    QRegularExpression R_date(Utils::dateRegex()); // dd/MM/yyyy
    QRegularExpressionValidator *valida = new QRegularExpressionValidator(R_date, this);
    textDeadline->setValidator(valida);

    // Set place holder for date lineedit
    textDeadline->setPlaceholderText("Example : " +Utils::dateFormat());
    mainLayout->addWidget(textDeadline, 2, 1);

    cmbReccurence = new QComboBox(this);
    cmbReccurence->addItem("Every Day", "Every Day");
    cmbReccurence->addItem("Every Two Week", "Every Two Week");
    cmbReccurence->addItem("Every Week", "Every Week");
    cmbReccurence->addItem("No Recurrence", "No Recurrence");
    mainLayout->addWidget(cmbReccurence, 4, 0);

    textDuration = new QLineEdit("", this);
    QRegularExpression R_duration(Utils::timeRegex()); // HH:mm:ss
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(R_duration, this);
    textDuration->setValidator(validator);

    // Set place holder for date lineedit
    textDuration->setPlaceholderText("Example : " + Utils::timeFormat());
    mainLayout->addWidget(textDuration, 4, 1);

    cmbParent = new QComboBox(this);

    mainLayout->addWidget(cmbParent, 6, 0);

    nudPriority = new QSpinBox(this);
    nudPriority->setMaximum(3);
    nudPriority->setMinimum(1);
    mainLayout->addWidget(nudPriority, 6, 1);

    //the close is differents depending if its add or update
    if (addDialog)
    {
        connect(btnSubmit, &QPushButton::released, this, &TaskDialog::addAndClose);
    }
    else
    {
        connect(btnSubmit, &QPushButton::released, this, &TaskDialog::updateAndClose);
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                          PRIVATE METHODS                          *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void TaskDialog::initialize(Task *task)
{
    this->task = task;

    cmbParent->clear();
    cmbParent->addItem("-", "");

    //If their is a Task set the values with it
    if (task != nullptr)
    {
        textName->setText(task->getName());
        textDeadline->setText(task->getDeadline().toString(Utils::dateFormat()));
        cmbReccurence->setCurrentIndex(cmbReccurence->findData(task->getRecurrenceString()));
        textDuration->setText(task->getDuration().toString());
        nudPriority->setValue(task->getPriority());

        for (Task *t : toDoList->getTasks())
        {
            if(t->getId()!=task->getId())
            {
                cmbParent->addItem(t->getName(), t->getId());
            }
        }

        if(task->getParents().size()>0)
        {
            Task *parent = task->getParents().at(0);
            cmbParent->setCurrentIndex(cmbParent->findData(parent->getId()));
        }
        else
        {
            cmbParent->setCurrentIndex(cmbParent->findData(""));
        }
    }
    else //no Task, the display is empty for a new Task
    {
        textName->clear();
        textDeadline->clear();

        textDuration->clear();

        cmbParent->setCurrentIndex(cmbParent->findData(""));
        nudPriority->setValue(1);
        for (Task *t : toDoList->getTasks())
        {
            cmbParent->addItem(t->getName(), t->getId());
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                            SLOTS                            *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//Create a new task and add it to the tdl
void TaskDialog::addAndClose()
{
    int priority = nudPriority->value();
    QString name = textName->text();

    if (name == "")
    {
        return;
    }

    QString time = textDeadline->text();
    if (!time.contains(QRegularExpression(Utils::dateRegex())) || time == "")
    {
        return;
    }

    QDateTime da = QDateTime::fromString(time, Utils::dateFormat());
    QDateTime deadline = (da);

    QDateTime startTime = QDateTime::currentDateTime();

    QString stringrecu = cmbReccurence->currentText();
    Recurrence recu = Recurrence::NO_RECURRENCE;

    if (stringrecu == "Every Day")
    {
        recu = Recurrence::EVERY_DAY;
    }
    else if (stringrecu == "Every Two Week")
    {
        recu = Recurrence::EVERY_TWO_WEEKS;
    }
    else if (stringrecu == "Every Week")
    {
        recu = Recurrence::EVERY_WEEK;
    }

    QString ts = textDuration->text();

    if (!ts.contains(QRegularExpression(Utils::timeRegex())) || ts == "") // dd:hh:mm
    {
        return;
    }

    TimeSpan timespan = Utils::stringToTime(ts);

    QList<Task *> parent;

    if (cmbParent->currentData().toString() != "")
    {
        int parentId = cmbParent->currentData().toInt();

        Task *p = this->toDoList->getTask(parentId);

        if (p != nullptr) parent.push_back(p);
    }

    Task *newTask = new Task(priority, name, deadline, startTime, timespan, recu);

    this->toDoList->addTask(newTask);

    foreach (Task *t, parent)
    {
        this->toDoList->addDependence(newTask, t);
    }

    emit taskAdded(newTask);

    this->close();
}

//Update the task that was given
void TaskDialog::updateAndClose()
{
    int priority = nudPriority->value();
    QString name = textName->text();
    if (name == "")
    {
        return;
    }

    QString time = textDeadline->text();
    if (!time.contains(QRegularExpression(Utils::dateRegex())) || time == "")
    {
        return;
    }

    QDateTime da = QDateTime::fromString(time, Utils::dateFormat());
    QDateTime deadline = (da);

    QDateTime startTime = QDateTime::currentDateTime();

    QString stringrecu = cmbReccurence->currentText();
    Recurrence recu = Recurrence::NO_RECURRENCE;

    if (stringrecu == "Every Day")
    {
        recu = Recurrence::EVERY_DAY;
    }
    else if (stringrecu == "Every Two Week")
    {
        recu = Recurrence::EVERY_TWO_WEEKS;
    }
    else if (stringrecu == "Every Week")
    {
        recu = Recurrence::EVERY_WEEK;
    }

    QString ts = textDuration->text();

    if (!ts.contains(QRegularExpression(Utils::timeRegex())) || ts == "") // dd:hh:mm
    {
        return;
    }

    TimeSpan timespan = Utils::stringToTime(ts);

    QList<Task *> parent;

    if (cmbParent->currentData().toString() != "")
    {
        int parentId = cmbParent->currentData().toInt();

        Task *p = this->toDoList->getTask(parentId);

        if (p != nullptr) parent.push_back(p);
    }

    task->setPriority(priority);
    task->setName(name);
    task->setDeadline(deadline);
    task->setStartTime(startTime);
    task->setDuration(timespan);
    task->setRecurrence(recu);

    // Remove old parents
    foreach (Task *t, task->getParents())
    {
        this->toDoList->removeDependence(task, t);
    }

    // Add new ones
    foreach (Task *t, parent)
    {
        this->toDoList->addDependence(task, t);
    }

    emit taskUpdated();

    this->close();
}
