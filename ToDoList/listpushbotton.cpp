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
    QString buttonStyle = QString("QPushButton { background-color: %1; border: none; color: white;"
                                  "padding: 10px 20px; text-align: center; text-decoration: none; "
                                  "display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; "
                                  "border-radius: 5px; }"
                                  "QPushButton:hover { background-color: #45a049; }"
                                  "QPushButton:pressed { background-color: #357a38; }").arg(tasklist->getColor());
    ui->list->setStyleSheet(buttonStyle);
}

listPushBotton::~listPushBotton()
{
    delete ui;
}

void listPushBotton::on_deleteList_clicked()
{
    QMessageBox::StandardButton reply;
    QString tmp ="Do you want to delete this task ?!";
    reply = QMessageBox::question(this, "confirmation", tmp,
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        taskList->deleteTaskList();
        hide();
    }
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

