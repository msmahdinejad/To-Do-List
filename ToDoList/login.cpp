#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("C:/saleh/UNI/AP/To Do List/uiap-final-project-msmahdinejad/Data.db");
    if(!DB.open())
        qDebug() << "DB in login page failed!";
    else
        qDebug() << "DB in login page opened!";

    ui->signupwidget->hide();
}

login::~login()
{
    delete ui;
}

void login::on_LoginInSignup_clicked()
{
    ui->signupwidget->hide();
    ui->loginwidget->show();
}


void login::on_SignUpInLogIn_clicked()
{
    ui->signupwidget->show();
    ui->loginwidget->hide();
}

bool login::checkLoginInputs()
{
    QString username, password;
    username = ui->usernameInLogIn->text();
    password = ui->PasswordInLogin->text();
    if(username.isEmpty() || password.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Fill in all the items!");
        return false;
    }
    QSqlQuery query;
    query.prepare("SELECT * FROM people WHERE username ='" + username + "'");
    if (!query.exec())
    {
        QMessageBox::critical(this, "Error", query.lastError().text());
        return false;
    }
    //QSqlRecord record = query.record();
    if (!query.next())
    {
        QMessageBox::critical(this, "Error", "Username not found!");
        return false;
    }
    QString DBPassword = query.value(1).toString();
    if(password != DBPassword)
    {
        QMessageBox::critical(this, "Error", "Password is not correct");
        return false;
    }
    return true;
}

bool login::checkSignupInputs()
{
    QString user, pass;
    user = ui->usernameInSignup->text();
    pass = ui->PasswordInSignup->text();
    if(user.isEmpty() || pass.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Fill in all the items!");
        return false;
    }
    if(user.size() < 8)
    {
        QMessageBox::critical(this, "Error", "Username must be at least 8 characters!");
        return false;
    }
    if(pass.size() < 8)
    {
        QMessageBox::critical(this, "Error", "Password must be at least 8 characters!");
        return false;
    }
    bool specialCheck = false;
    QString specialCharacters = "!@#$%^&*()_+{}|:\"<>?-=[]\\;',./";
    for (const QChar &ch : specialCharacters) {
        if (pass.contains(ch)) {
            specialCheck = true;
            break;
        }
    }
    if(!specialCheck)
    {
        QMessageBox::critical(this, "Error", "Password must contain special characters!");
        return false;
    }
    bool capitalCheck = false;
    bool numbersCheck = false;
    for (const QChar &ch : pass) {
        if (ch.isUpper()) {
            capitalCheck = true;
        }
        if(ch >= '0' && ch <= '9')
        {
            numbersCheck = true;
        }
    }
    if(!capitalCheck)
    {
        QMessageBox::critical(this, "Error", "Password must contain capital letters!");
        return false;
    }
    if(!numbersCheck)
    {
        QMessageBox::critical(this, "Error", "Password must contain numbers!");
        return false;
    }
    QSqlQuery query;
    query.prepare("SELECT * FROM people WHERE username ='" + user + "'");
    if (!query.exec())
    {
        QMessageBox::critical(this, "Error", query.lastError().text());
        return false;
    }
    //QSqlRecord record = query.record();
    if (!query.next())
    {
        return true;
    }
    QMessageBox::critical(this, "Error", "Username already exist!");
    return false;
}


void login::on_loginBotton_clicked()
{
    if(checkLoginInputs())
    {
        // userWidget * UW = new userWidget(ui->usernameInLogIn->text());
        // UW->show();
        DB.close();
        this->hide();
    }
}


void login::on_signupBotton_clicked()
{
    if(checkSignupInputs())
    {
        QSqlQuery query;
        query.prepare("INSERT INTO people (username, password) VALUES ('" + ui->usernameInSignup->text()+ "', '" + ui->PasswordInSignup->text() + "')");
        if (!query.exec())
        {
            QMessageBox::critical(this, "Error", query.lastError().text());
            return;
        }
        else
        {
            ui->usernameInSignup->setText("");
            ui->PasswordInSignup->setText("");
            QMessageBox::information(this, "Success", "Sing up was succefully!");
            return;
        }
    }
}

