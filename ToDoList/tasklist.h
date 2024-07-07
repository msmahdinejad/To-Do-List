#ifndef TASKLIST_H
#define TASKLIST_H

#include <QWidget>
#include "linklist.h"
#include "task.h"
#include <QVBoxLayout>

namespace Ui {
class TaskList;
}

class TaskList : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout * layout;
    QSqlDatabase DB;
    QString name;
    QString color;
    QString user;
    int removable;
    LinkList<Task> * tasks;

public:
    TaskList(QString name, QString color, QString user, int removable = 1, QWidget *parent = nullptr);
    ~TaskList();
    void addTask(QString taskName);
    void removeTask(int id);
    void deleteTaskList();
    QString & getName();
    QString & getColor();
    QString & getUser();
    LinkList<Task> * getTasks();
    void loadData();
    void saveList();

private slots:
    void on_pushButton_clicked();

private:
    Ui::TaskList *ui;
};

#endif // TASKLIST_H
