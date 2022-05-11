#include "taskdialog.h"

TaskDialog::TaskDialog(QWidget *_parent) : QDialog(_parent)
{
    // toDoList->addTask(TabModel::createTask());

    mainLayout = new QGridLayout(this);

    labelTitle = new QLabel("Create New Task");
    QFont font = labelTitle->font();
    font.setUnderline(1);
    labelTitle->setFont(font);
    labelTitle->setMaximumHeight(20);
    mainLayout->addWidget(labelTitle);

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

    btnSubmit = new QPushButton("Submit", this);
    mainLayout->addWidget(btnSubmit, 7, 1);

    textName = new QLineEdit("", this);
    mainLayout->addWidget(textName, 2, 0);

    textDeadline = new QLineEdit("", this);
    QRegularExpression R_date("(0[1-9]|[12][0-9]|3[01])/(0[1-9]|[1][0-2])/(20[0-9][0-9])");
    QRegularExpressionValidator *valida = new QRegularExpressionValidator(R_date, this);
    textDeadline->setValidator(valida);

    // Set place holder for date lineedit
    textDeadline->setPlaceholderText("Example : 21/05/2019");
    mainLayout->addWidget(textDeadline, 2, 1);

    cmbReccurence = new QComboBox(this);
    cmbReccurence->addItem("Every Day");
    cmbReccurence->addItem("Every Two Week");
    cmbReccurence->addItem("Every Week");
    cmbReccurence->addItem("No Recurrence");
    mainLayout->addWidget(cmbReccurence, 4, 0);

    textDuration = new QLineEdit("", this);
    QRegularExpression R_duration("^((?:[01]\d|2[0-3]):[0-5]\d:[0-5]\d$)"); // dd:HH:mm
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(R_duration, this);
    textDuration->setValidator(validator);

    // Set place holder for date lineedit
    textDuration->setPlaceholderText("Example : 12:05:05");
    mainLayout->addWidget(textDuration, 4, 1);

    cmbParent = new QComboBox(this);
    cmbParent->addItem("TESTTESTEST");
    cmbParent->addItem("");
    mainLayout->addWidget(cmbParent, 6, 0);

    // LA TODOLIST A UNE TAILLE DE 4 (TODO)
    //    for(int i= 0;i<4;i++)
    //    {
    //        cmbParent->addItem();
    //    }
    nudPriority = new QSpinBox(this);
    nudPriority->setMaximum(3);
    nudPriority->setMinimum(1);
    mainLayout->addWidget(nudPriority, 6, 1);

    connect(btnSubmit, &QPushButton::pressed, this, &TaskDialog::saveAndClose);
}

TaskDialog::TaskDialog(Task task, QWidget *_parent) : QDialog(_parent)
{

    // toDoList->addTask(TabModel::createTask());

    mainLayout = new QGridLayout(this);

    labelTitle = new QLabel("Create New Task");
    QFont font = labelTitle->font();
    font.setUnderline(1);
    labelTitle->setFont(font);
    labelTitle->setMaximumHeight(20);
    mainLayout->addWidget(labelTitle);

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

    btnSubmit = new QPushButton("Submit", this);
    mainLayout->addWidget(btnSubmit, 7, 1);

    textName = new QLineEdit("", this);
    mainLayout->addWidget(textName, 2, 0);

    textDeadline = new QLineEdit("", this);
    QRegularExpression R_date("(0[1-9]|[12][0-9]|3[01])/(0[1-9]|[1][0-2])/(20[0-9][0-9])"); // dd/MM/yyyy
    QRegularExpressionValidator *valida = new QRegularExpressionValidator(R_date, this);
    textDeadline->setValidator(valida);

    // Set place holder for date lineedit
    textDeadline->setPlaceholderText("Example : 21/05/2019");
    mainLayout->addWidget(textDeadline, 2, 1);

    cmbReccurence = new QComboBox(this);
    cmbReccurence->addItem("Every Day", "Every Day");
    cmbReccurence->addItem("Every Two Week", "Every Two Week");
    cmbReccurence->addItem("Every Week", "Every Week");
    cmbReccurence->addItem("No Recurrence", "No Recurrence");
    mainLayout->addWidget(cmbReccurence, 4, 0);

    textDuration = new QLineEdit("", this);
    QRegularExpression R_duration("^((?:[01]|2[0-3]):[0-5]:[0-5]$)"); // HH:mm:ss
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(R_duration, this);
    textDuration->setValidator(validator);

    // Set place holder for date lineedit
    textDuration->setPlaceholderText("Example : 12:05:05");
    mainLayout->addWidget(textDuration, 4, 1);

    cmbParent = new QComboBox(this);
    cmbParent->addItem("TESTTESTEST", "TESTTESTEST");
    cmbParent->addItem("", "");
    mainLayout->addWidget(cmbParent, 6, 0);

    // LA TODOLIST A UNE TAILLE DE 4 (TODO)
    //    for(int i= 0;i<4;i++)
    //    {
    //        cmbParent->addItem(todolist.getElementAt(i).text());
    //    }
    nudPriority = new QSpinBox(this);
    nudPriority->setMaximum(3);
    nudPriority->setMinimum(1);
    mainLayout->addWidget(nudPriority, 6, 1);

    connect(btnSubmit, &QPushButton::pressed, this, &TaskDialog::saveAndClose);

    // TaskDialog();
    textName->setText(task.getName());
    textDeadline->setText(task.getDeadline().toString());
    cmbReccurence->setCurrentIndex(cmbReccurence->findData(task.getRecurrenceString()));
    textDuration->setText(task.getDuration().toString());

    cmbParent->setCurrentIndex(cmbParent->findData(""));
    nudPriority->setValue(task.getPriority());
}

void TaskDialog::saveAndClose()
{
    TaskStatus status;
    int priority = nudPriority->value();
    QString name = textName->text();
    if (name == "")
    {
        return;
    }

    QString time = textDeadline->text();
    if (!time.contains(QRegularExpression("(0[1-9]|[12][0-9]|3[01])/(0[1-9]|[1][0-2])/(20[0-9][0-9])")) || time == "")
    {
        return;
    }

    QDateTime da = QDateTime::fromString(time, "dd/MM/yyyy");
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

    if (!ts.contains(QRegularExpression("^((?:[01]|2[0-3]):[0-5]:[0-5]$)")) || ts == "") // dd:hh:mm
    {
        return;
    }

    TimeSpan timespan = Utils::stringToTime(ts);

    QList<Task *> parent;
    if (!(cmbParent->currentText() == ""))
    { // A parent exists

        // Get la tâche associé au current Text en parcourant todolis
    }
    // Je sais pas comment faire pour avoir les parents vu que dans la combobox c'es tstocké en string
    Task *newTask = new Task(status, priority, name, deadline, startTime, timespan, recu, parent);
    QMessageBox::information(this, "Ajout d'une tâches", newTask->readTask());
    newTask->deleteTask(*newTask);
    this->close();
}
