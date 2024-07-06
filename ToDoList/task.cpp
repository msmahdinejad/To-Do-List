#include "task.h"
#include "ui_task.h"

Task::Task(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Task)
{
    ui->setupUi(this);
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("C:/saleh/UNI/AP/To Do List/uiap-final-project-msmahdinejad/Data.db");
    if(!DB.open())
        qDebug() << "DB in Task page failed!";
    else
        qDebug() << "DB in Task page opened!";\

}

Task::~Task()
{
    delete ui;
}

void Task::on_check_stateChanged(int s)
{
    if(s == Qt::Checked)
    {
        ui->name->setStyleSheet("QLabel { text-decoration: line-through; color: gray;}");
        check = 1;
        QSqlQuery query;
        query.prepare("UPDATE task SET check = ? WHERE ID = ?");
        query.addBindValue(check);
        query.addBindValue(ID);
        if (!query.exec()) {
            qDebug() << "Error updating check: " << query.lastError();
        }
    }
    else
    {
        ui->name->setStyleSheet("QLabel { text-decoration: none; color: black;}");
        check = 0;
        QSqlQuery query;
        query.prepare("UPDATE task SET check = ? WHERE ID = ?");
        query.addBindValue(check);
        query.addBindValue(ID);
        if (!query.exec()) {
            qDebug() << "Error updating check: " << query.lastError();
        }
    }
}


void Task::on_star_stateChanged(int s)
{
    if(s == Qt::Checked)
    {
        star = 1;
        QSqlQuery query;
        query.prepare("UPDATE task SET star = ? WHERE ID = ?");
        query.addBindValue(star);
        query.addBindValue(ID);
        if (!query.exec()) {
            qDebug() << "Error updating star: " << query.lastError();
        }
    }
    else
    {
        star = 0;
        QSqlQuery query;
        query.prepare("UPDATE task SET star = ? WHERE ID = ?");
        query.addBindValue(star);
        query.addBindValue(ID);
        if (!query.exec()) {
            qDebug() << "Error updating star: " << query.lastError();
        }
    }
}

