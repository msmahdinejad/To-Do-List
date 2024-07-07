#include "userdata.h"

UserData::UserData(QString username)
{
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("C:/saleh/UNI/AP/To Do List/uiap-final-project-msmahdinejad/Data.db");
    if(!DB.open())
        qDebug() << "DB in userData failed!";
    else
        qDebug() << "DB in userData opened!";

    QSqlQuery query2;
    query2.prepare("SELECT * FROM list WHERE user = ?");
    if (!query2.exec())
    {
        qDebug() << "Error read list : " << query2.lastError();
    }
    else
    {
        while(query2.next())
        {
            QString name = query2.value(0).toString();
            QString user = query2.value(1).toString();
            QString color = query2.value(2).toString();
            int removable = query2.value(3).toInt();
            TaskList * taskList = new TaskList(name, user, color, removable);
            lists->push_back(taskList);
            qDebug() << "list loaded succefully!";
        }
    }
}
void UserData::addList(QString name, QString color)
{
    TaskList * taskList = new TaskList(name, username, color);
    taskList->saveList();
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
