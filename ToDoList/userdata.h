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
    vector<TaskList *> * lists;
public:
    UserData(QString username);
    void addList(QString name, QString color);
    void removeList(QString name);
    vector<TaskList *> * getLists();
};

#endif // USERDATA_H
