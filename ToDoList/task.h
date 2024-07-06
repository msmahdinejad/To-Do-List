#ifndef TASK_H
#define TASK_H

#include <QWidget>

namespace Ui {
class Task;
}

class Task : public QWidget
{
    Q_OBJECT

private:
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
    explicit Task(QWidget *parent = nullptr);
    ~Task();


private:
    Ui::Task *ui;
};

#endif // TASK_H
