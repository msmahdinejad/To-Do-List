#ifndef USERDATA_H
#define USERDATA_H

#include <bits/stdc++.h>
#include <QString>
#include <tasklist.h>
#include <QIntValidator>
#include <QMessageBox>
#include <QDebug>
#include <QtSql>
#include <QFileInfo>


using namespace std;

class UserData
{
    QSqlDatabase DB;
    QString username;
    QString password;
    set<TaskList> * lists;
public:
    UserData(QString username);
    void addList(QString name, QString color);
    void removeList(QString name);
    set<QString> * getListnames();
    map<QString, TaskList> * getLists();
};

#endif // USERDATA_H
