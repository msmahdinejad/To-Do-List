#include "task.h"
#include "ui_task.h"

Task::Task(int id, QString user, QString list, QString name, int check, int star, QString caption, int assigncheck, QString assignuser, int year, int month, int day, QWidget *parent)
    : QWidget(parent)
    , ID(id)
    , user(user)
    , list(list)
    , name(name)
    , check(check)
    , star(star)
    , caption(caption)
    , assignCheck(assigncheck)
    , assignUser(assignuser)
    , year(year)
    , month(month)
    , day(day)
    , ui(new Ui::Task)
{
    ui->setupUi(this);
    ui->name->setText(name);
    if(check == 1)
    {
        ui->check->setCheckState(Qt::Checked);
        ui->name->setStyleSheet("QLabel { text-decoration: line-through; color: gray;}");
    }
    if(star == 1)
    {
        ui->star->setCheckState(Qt::Checked);
    }

}

Task::~Task()
{
    delete ui;
}

void Task::on_check_stateChanged(int s)
{

}


void Task::on_star_stateChanged(int s)
{

}

void Task::save()
{
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("C:/saleh/UNI/AP/To Do List/uiap-final-project-msmahdinejad/Data.db");
    if(!DB.open())
        qDebug() << "DB in Task page failed!";
    else
        qDebug() << "DB in Task page opened!";
    QSqlQuery query;
    query.prepare("UPDATE task SET name = ?, caption = ?, assigncheck = ?, assignuser = ?, year = ?, month = ?, day = ? WHERE ID = ?");
    query.addBindValue(name);
    query.addBindValue(caption);
    query.addBindValue(assignCheck);
    query.addBindValue(assignUser);
    query.addBindValue(year);
    query.addBindValue(month);
    query.addBindValue(day);
    query.addBindValue(ID);
    if (!query.exec()) {
        qDebug() << "Error Save : " << query.lastError();
    }
    DB.close();
}
void Task::remove()
{
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("C:/saleh/UNI/AP/To Do List/uiap-final-project-msmahdinejad/Data.db");
    if(!DB.open())
        qDebug() << "DB in Task page failed!";
    else
        qDebug() << "DB in Task page opened!";
    QSqlQuery query;
    query.prepare("DELETE FROM task WHERE ID = ?");
    query.addBindValue(ID);
    if (!query.exec()) {
        qDebug() << "Error removing Task: " << query.lastError();
    }
    DB.close();
    this->hide();
}
QString & Task::getName(){return name;}
QString & Task::getCaption(){return caption;}
int & Task::getAssignCheck(){return assignCheck;}
QString & Task::getAssignUser(){return assignUser;}
int & Task::getYear(){return year;}
int & Task::getMonth(){return month;}
int & Task::getDay(){return day;}
void Task::setName(QString Name){name = Name;}
void Task::setCaption(QString Caption){caption = Caption;}
void Task::setAssignCheck(int AssignCheck){assignCheck = AssignCheck;}
void Task::setAssignUser(QString AssignUser){assignUser = AssignUser;}
void Task::setYear(int Year){year = Year;}
void Task::setMonth(int Month){month = Month;}
void Task::setDay(int Day){day = Day;}
int & Task::getID(){return ID;}

void Task::on_pushButton_clicked()
{
    emit buttonClicked(this);
}


void Task::on_star_clicked()
{
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("C:/saleh/UNI/AP/To Do List/uiap-final-project-msmahdinejad/Data.db");
    if(!DB.open())
        qDebug() << "DB in Task page failed!";
    else
        qDebug() << "DB in Task page opened!";
    if(ui->star->isChecked())
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
    DB.close();
}


void Task::on_check_clicked()
{
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("C:/saleh/UNI/AP/To Do List/uiap-final-project-msmahdinejad/Data.db");
    if(!DB.open())
        qDebug() << "DB in Task page failed!";
    else
        qDebug() << "DB in Task page opened!";
    if(ui->check->isChecked())
    {
        check = 1;
        QSqlTableModel model;
        model.setTable("task");
        model.setFilter(QString("ID = %1").arg(ID));
        model.select();

        if (model.rowCount() == 1) {
            model.setData(model.index(0, model.fieldIndex("check")), check);
            if (!model.submitAll()) {
                qDebug() << "Error updating check: " << model.lastError();
            } else {
                qDebug() << "Task updated successfully";
            }
        } else {
            qDebug() << "Task not found or multiple tasks with the same ID";
        }
        ui->name->setStyleSheet("QLabel { text-decoration: line-through; color: gray;}");
    }
    else
    {
        check = 0;
        QSqlTableModel model;
        model.setTable("task");
        model.setFilter(QString("ID = %1").arg(ID));
        model.select();

        if (model.rowCount() == 1) {
            model.setData(model.index(0, model.fieldIndex("check")), check);
            if (!model.submitAll()) {
                qDebug() << "Error updating check: " << model.lastError();
            } else {
                qDebug() << "Task updated successfully";
            }
        } else {
            qDebug() << "Task not found or multiple tasks with the same ID";
        }
        ui->name->setStyleSheet("QLabel { text-decoration: none; color: black;}");
    }
    DB.close();
}

