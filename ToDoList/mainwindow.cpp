#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QLabel>
#include<QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QVBoxLayout * temp = new QVBoxLayout(this);
    for(int i = 0; i < 10; i++)
    {
        QLabel * t = new QLabel("salamasklndsadakdjaksjdlaskdajsldkjksak");
        temp->addWidget(t);
    }

    ui->scrollAreaWidgetContents->setLayout(temp);
}

MainWindow::~MainWindow()
{
    delete ui;
}
