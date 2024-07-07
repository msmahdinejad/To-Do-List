#include "tasklist.h"
#include "ui_tasklist.h"
#include <QPushButton>

TaskList::TaskList(QString name, QString User, QString color, int removable, QWidget *parent)
    : QWidget(parent)
    , name(name)
    , user(User)
    , color(color)
    , removable(removable)
    , ui(new Ui::TaskList)
{
    ui->setupUi(this);
    tasks = new LinkList<Task>();

    layout = new QVBoxLayout();
    ui->scrollAreaWidgetContents->setLayout(layout);
}

TaskList::~TaskList()
{
    delete ui;
}

void TaskList::saveList()
{
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("C:/saleh/UNI/AP/To Do List/uiap-final-project-msmahdinejad/Data.db");
    if(!DB.open())
        qDebug() << "DB in Tasklist failed!";
    else
        qDebug() << "DB in Tasklist opened!";
    QSqlQuery query;
    query.prepare("INSERT INTO list (name, user, color, removable) VALUES (?, ?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(user);
    query.addBindValue(color);
    query.addBindValue(removable);
    if (!query.exec()) {
        qDebug() << "Error add list : " << query.lastError();
    }
}

void TaskList::loadData()
{
    node<Task> * tmp = tasks->getHead();

    while(tmp != 0)
    {
        node<Task> * tmp2 = tmp->getNext();
        tmp->getData()->hide();
        tmp = tmp2;
    }
    tasks->deleteList();

    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("C:/saleh/UNI/AP/To Do List/uiap-final-project-msmahdinejad/Data.db");
    if(!DB.open())
        qDebug() << "DB in Tasklist failed!";
    else
        qDebug() << "DB in Tasklist opened!";
    QSqlQuery query2;
    if(name.contains("/star"))
    {
        query2.prepare("SELECT * FROM task WHERE user = ? AND star = ?");
        query2.addBindValue(user);
        query2.addBindValue(1);
    }
    else if(name.contains("/IAssigned"))
    {
        query2.prepare("SELECT * FROM task WHERE user = ? AND assigncheck = ?");
        query2.addBindValue(user);
        query2.addBindValue(1);
    }
    else if(name.contains("/AssignedToMe"))
    {
        query2.prepare("SELECT * FROM task WHERE assignuser = ? AND assigncheck = ?");
        query2.addBindValue(user);
        query2.addBindValue(1);
    }
    else
    {
        query2.prepare("SELECT * FROM task WHERE user = ? AND list = ?");
        query2.addBindValue(user);
        query2.addBindValue(name);
    }
    if (!query2.exec())
    {
        qDebug() << "Error read Task : " << query2.lastError();
    }
    else
    {
        while(query2.next())
        {
            int id = query2.value(0).toInt();
            QString user = query2.value(1).toString();
            QString list = query2.value(2).toString();
            QString name = query2.value(3).toString();
            int check = query2.value(4).toInt();
            int star = query2.value(5).toInt();
            QString caption = query2.value(6).toString();
            int assigncheck = query2.value(7).toInt();
            QString assignuser = query2.value(8).toString();
            int year = query2.value(9).toInt();
            int month = query2.value(10).toInt();
            int day = query2.value(11).toInt();
            Task * task = new Task(id, user, list, name, check, star, caption, assigncheck, assignuser, year, month, day);
            tasks->push_front(task);
            layout->addWidget(task);
            qDebug() << "task loaded succefully!";
        }
    }
    ui->scrollAreaWidgetContents->setLayout(layout);
}

void TaskList::addTask(QString taskName)
{
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("C:/saleh/UNI/AP/To Do List/uiap-final-project-msmahdinejad/Data.db");
    if(!DB.open())
        qDebug() << "DB in Tasklist failed!";
    else
        qDebug() << "DB in Tasklist opened!";
    QSqlQuery query;
    query.prepare("INSERT INTO task (user, list, name) VALUES (?, ?, ?)");
    query.addBindValue(user);
    query.addBindValue(name);
    query.addBindValue(taskName);
    if (!query.exec()) {
        qDebug() << "Error add Task : " << query.lastError();
    }
    int id = query.lastInsertId().toInt();
    QSqlQuery query2;
    query2.prepare("SELECT * FROM task WHERE ID ='" + QString::fromStdString(std::to_string(id)) + "'");
    if (!query2.exec())
    {
        qDebug() << "Error read Task : " << query2.lastError();
    }
    else
    {
        while(query2.next())
        {
            int id = query2.value(0).toInt();
            QString user = query2.value(1).toString();
            QString list = query2.value(2).toString();
            QString name = query2.value(3).toString();
            int check = query2.value(4).toInt();
            int star = query2.value(5).toInt();
            QString caption = query2.value(6).toString();
            int assigncheck = query2.value(7).toInt();
            QString assignuser = query2.value(8).toString();
            int year = query2.value(9).toInt();
            int month = query2.value(10).toInt();
            int day = query2.value(11).toInt();
            Task * task = new Task(id, user, list, name, check, star, caption, assigncheck, assignuser, year, month, day);
            tasks->push_front(task);
            layout->addWidget(task);
            qDebug() << "task loaded succefully!";
        }
    }
    ui->scrollAreaWidgetContents->setLayout(layout);
}
void TaskList::removeTask(int id)
{
    if (tasks->getHead()) {
        if (tasks->getHead()->getData()->getID() == id)
        {
            node<Task> * tmp = tasks->getHead();
            tasks->setNode(tasks->getHead(), tasks->getHead()->getNext());
            tmp->getData()->remove();
            delete tmp;
            return;
        }
    }
    node<Task> * tmp = tasks->getHead();
    while (tmp)
    {
        if (tmp->getNext()->getData()->getID() == id ) {
            node<Task> * t2 = tmp->getNext() ;
            tasks->setNode(tmp->getNext(), tmp->getNext()->getNext());
            t2->getData()->remove();
            delete t2 ;
            return ;
        }
        tmp = tmp->getNext();
    }
}
void TaskList::deleteTaskList()
{
    node<Task> * tmp = tasks->getHead();
    while(tmp != 0)
    {
        node<Task> * tmp2 = tmp->getNext();
        tmp->getData()->remove();
        tmp = tmp2;
    }
    tasks->deleteList();
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("C:/saleh/UNI/AP/To Do List/uiap-final-project-msmahdinejad/Data.db");
    if(!DB.open())
        qDebug() << "DB in Tasklist failed!";
    else
        qDebug() << "DB in Tasklist opened!";
    QSqlQuery query;
    query.prepare("DELETE FROM list WHERE user = ? AND name = ?");
    query.addBindValue(user);
    query.addBindValue(name);
    if (!query.exec()) {
        qDebug() << "Error removing list: " << query.lastError();
    }

    hide();
}
QString & TaskList::getName(){return name;}
QString & TaskList::getColor(){return color;}
QString & TaskList::getUser(){return user;}
LinkList<Task> * TaskList::getTasks(){return tasks;}
int & TaskList::getRemovable(){return removable;}
void TaskList::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::critical(this, "Error", "Task must have a name!");
    }
    else
    {
        addTask(ui->lineEdit->text());
    }
}

