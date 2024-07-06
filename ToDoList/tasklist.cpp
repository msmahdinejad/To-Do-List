#include "tasklist.h"
#include "ui_tasklist.h"

TaskList::TaskList(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TaskList)
{
    ui->setupUi(this);
}

TaskList::~TaskList()
{
    delete ui;
}
