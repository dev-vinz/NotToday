#include "taskmanagement.h"

TaskManagement::TaskManagement(QWidget *_parent) : TabModel(_parent)
{
    mainLayout = new QGridLayout(this);
    topLayout = new QHBoxLayout(this);
    boardLayout = new QGridLayout(this);

    mainLayout->addLayout(topLayout,0,0);
    mainLayout->addLayout(boardLayout,1,0);

    lblTitle = new QLabel("Aperçu des tâches");
    QFont font = lblTitle->font();
    font.setUnderline(1);
    lblTitle->setFont(font);
    topLayout->addWidget(lblTitle);

    btnAddTask = new QPushButton("Ajouter une Tâche", this);
    btnAddTask->setGeometry(500,50,150,50);
    topLayout->addWidget(btnAddTask);

    btnRemoveTask = new QPushButton("Supprimer Tâche", this);
    btnRemoveTask->setGeometry(600,50,150,50);
    topLayout->addWidget(btnRemoveTask);

    btnModifyTask = new QPushButton("Modifier Tâche",this);
    btnModifyTask->setGeometry(700,50,150,50);
    topLayout->addWidget(btnModifyTask);

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


    connect(btnAddTask, &QPushButton::clicked, this, &TaskManagement::openNewWindow);
    connect(btnModifyTask, &QPushButton::clicked,this, &TaskManagement::openNewWindow);
    //connect(btnRemoveTask, &QPushButton::clicked, this, &Task::deleteTask);
}
void TaskManagement::openNewWindow()
{
    QObject *emmetteur = sender();
    if(emmetteur==btnModifyTask)
    {
        modifyTask = new QWindow();
        modifyTask->setTitle("Modify Task");
        modifyTask->show();
    }else
    {
        addTask = new QWindow();
        addTask->setTitle("Add Task");
        addTask->show();
       /*
         * // Create another type of window AddTaskWindow that extends from QWindow
        DEstroy??
        */
    }
}



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                          PROTECTED                          *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void TaskManagement::initialize()
{

}
