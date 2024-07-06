#ifndef TASKLIST_H
#define TASKLIST_H

#include <QWidget>

namespace Ui {
class TaskList;
}

class TaskList : public QWidget
{
    Q_OBJECT

public:
    explicit TaskList(QWidget *parent = nullptr);
    ~TaskList();

private:
    Ui::TaskList *ui;
};

#endif // TASKLIST_H
