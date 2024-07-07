#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QColorDialog>
#include "listpushbotton.h"

MainWindow::MainWindow(UserData * mydata, QWidget *parent)
    : QMainWindow(parent)
    , MyData(mydata)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    layout = new QVBoxLayout();
    for(auto v = mydata->getLists()->begin(); v != mydata->getLists()->end(); v++)
    {

        listPushBotton * temp = new listPushBotton(*v);
        layout->addWidget(temp);
        connect(temp, &listPushBotton::buttonClicked, this, &MainWindow::on_tasklist_clicked);
    }
    ui->scrollAreaWidgetContents->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tasklist_clicked(TaskList * taskList)
{
    ui->stackedWidget->insertWidget(1, taskList);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_2_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
    MyData->addList(ui->lineEdit->text(), color.name());
    auto v = MyData->getLists()->rbegin();
    listPushBotton * temp = new listPushBotton(*v);
    layout->addWidget(temp);
    ui->scrollAreaWidgetContents->setLayout(layout);
}

