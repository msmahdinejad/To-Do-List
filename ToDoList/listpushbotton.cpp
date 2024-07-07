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

