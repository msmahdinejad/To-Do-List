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
    Task * selectedTask;
    QVBoxLayout * layout;
    QSqlDatabase DB;
    QString name;
    QString user;
    QString color;
    int removable;
    LinkList<Task> * tasks;

public:
    TaskList(QString name, QString user, QString color, int removable = 1, QWidget *parent = nullptr);
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
    int & getRemovable();
    void selectTask(Task * temp);
    bool checkEditInputs();
    void printData();


private slots:
    void on_pushButton_clicked();

    void on_Delete_clicked();

    void on_Edit_clicked();

    void on_task_clicked(Task * task);

private:
    Ui::TaskList *ui;
};

#endif // TASKLIST_H
