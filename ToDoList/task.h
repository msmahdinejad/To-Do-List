#ifndef TASK_H
#define TASK_H

#include <QWidget>
#include <QIntValidator>
#include <QMessageBox>
#include <QDebug>
#include <QtSql>
#include <QFileInfo>

namespace Ui {
class Task;
}

class Task : public QWidget
{
    Q_OBJECT

private:
    QSqlDatabase DB;
    int ID;
    QString user;
    QString list;
    QString name;
    int check;
    int star;
    QString caption;
    int assignCheck;
    QString assignUser;
    int year;
    int month;
    int day;

public:
    Task(int id, QString user, QString list, QString name, int check, int star, QString caption, int assigncheck, QString assignuser, int year, int month, int day, QWidget *parent = nullptr);
    ~Task();
    void save();
    void remove();
    QString & getName();
    QString & getCaption();
    int & getAssignCheck();
    QString & getAssignUser();
    int & getYear();
    int & getMonth();
    int & getDay();
    void setName(QString name);
    void setCaption(QString caption);
    void setAssignCheck(int assignCheck);
    void setAssignUser(QString assignUser);
    void setYear(int year);
    void setMonth(int month);
    void setDay(int day);
    int & getID();

private slots:
    void on_check_stateChanged(int arg1);

    void on_star_stateChanged(int arg1);

    void on_pushButton_clicked();

    void on_star_clicked();

    void on_check_clicked();

signals:
    void buttonClicked(Task * task);


private:
    Ui::Task *ui;
};

#endif // TASK_H
