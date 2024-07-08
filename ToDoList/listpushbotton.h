#ifndef LISTPUSHBOTTON_H
#define LISTPUSHBOTTON_H

#include <QWidget>
#include <tasklist.h>

namespace Ui {
class listPushBotton;
}

class listPushBotton : public QWidget
{
    Q_OBJECT

    TaskList * taskList;
public:
    explicit listPushBotton(TaskList * tasklist, QWidget *parent = nullptr);
    ~listPushBotton();

signals:
    void buttonClicked(TaskList * taskList);

private slots:
    void on_deleteList_clicked();

    void on_list_clicked();

    void on_print_clicked();

private:
    Ui::listPushBotton *ui;
    QWidget * Parent;
};

#endif // LISTPUSHBOTTON_H
