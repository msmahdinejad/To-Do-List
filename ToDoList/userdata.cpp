#include "userdata.h"

UserData::UserData(QString UserName)
{
    username = UserName;
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("C:/saleh/UNI/AP/To Do List/uiap-final-project-msmahdinejad/Data.db");
    if(!DB.open())
        qDebug() << "DB in userData failed!";
    else
        qDebug() << "DB in userData opened!";
    lists = new vector<TaskList *>();
    QSqlQuery query;
    query.prepare("SELECT * FROM list WHERE user = ?");
    query.addBindValue(username);
    if (!query.exec())
    {
        qDebug() << "Error read list : " << query.lastError();
    }
    while(query.next())
    {
        QString name = query.value(0).toString();
        QString user = query.value(1).toString();
        QString color = query.value(2).toString();
        int removable = query.value(3).toInt();
        TaskList * taskList = new TaskList(name, user, color, removable);
        lists->push_back(taskList);
        qDebug() << "list loaded succefully!";
    }
    for(auto v = lists->begin(); v != lists->end(); v++)
    {
        (*v)->reminderCheck();
    }
}
void UserData::addList(QString name, QString color)
{
    TaskList * taskList = new TaskList(name, username, color);
    taskList->saveList();
    lists->push_back(taskList);
}
void UserData::removeList(QString name)
{
    for(auto v = lists->begin(); v != lists->end(); v++)
    {
        if((*v)->getName() == name)
        {
            (*v)->deleteTaskList();
            lists->erase(v);
            return;
        }
    }
}
vector<TaskList *> * UserData::getLists(){return lists;}
