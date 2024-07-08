#include "listpushbotton.h"
#include "ui_listpushbotton.h"

listPushBotton::listPushBotton(TaskList * tasklist, QWidget *parent)
    : QWidget(parent)
    , taskList(tasklist)
    , ui(new Ui::listPushBotton)
{
    Parent = parent;
    ui->setupUi(this);
    if(tasklist->getRemovable() == 0)
        ui->deleteList->hide();
    else
        ui->deleteList->show();
    if(tasklist->getName().contains("/star"))
        ui->list->setText("Important");
    else if(tasklist->getName().contains("/AssignedToMe"))
        ui->list->setText("Assigned To Me");
    else if(tasklist->getName().contains("/IAssigned"))
        ui->list->setText("I Assigned");
    else
        ui->list->setText(tasklist->getName());
    QString buttonStyle = QString("background-color: %1; color: white;").arg(tasklist->getColor());
    ui->list->setStyleSheet(buttonStyle);
}

listPushBotton::~listPushBotton()
{
    delete ui;
}

void listPushBotton::on_deleteList_clicked()
{
    taskList->deleteTaskList();
    hide();
}


void listPushBotton::on_list_clicked()
{
    taskList->loadData();
    emit buttonClicked(taskList);
}


void listPushBotton::on_print_clicked()
{
    taskList->printData();
}

