#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "userdata.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    UserData * MyData;

public:
    MainWindow(UserData * mydata, QWidget *parent = nullptr);
    ~MainWindow();
    bool checkInput();

private slots:
    void on_tasklist_clicked(TaskList * taskList);
    void on_pushButton_2_clicked();

private:
    QVBoxLayout * layout;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
