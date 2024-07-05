#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QIntValidator>
#include <QMessageBox>
#include <QDebug>
#include <QtSql>
#include <QFileInfo>

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

private:
    QSqlDatabase DB;

private:
    bool checkLoginInputs();
    bool checkSignupInputs();

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_LoginInSignup_clicked();

    void on_SignUpInLogIn_clicked();

    void on_loginBotton_clicked();

    void on_signupBotton_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
