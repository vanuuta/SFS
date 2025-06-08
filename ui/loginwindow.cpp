#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "registerwindow.h"
#include "studentwindow.h"
#include "teacherwindow.h"
#include "adminwindow.h"

#include <QSqlError>
LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->errorLabel->setText("");
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    QString username = ui->loginLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text(); // в будущем можно хешировать

    authenticateUser(username, password);
}
//TODO  Сделать окна для админа и пользователя
void LoginWindow::authenticateUser(const QString &username, const QString &password)
{
    QSqlQuery query;
    // QString group;
    query.prepare("SELECT role, group_number FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    // query.bindValue(":group_number", group);
    User user;
    user.password = password;
    user.username = username;
    // user.group    = group;
    if (!query.exec()) {
        qDebug() << "Query error:" << query.lastError().text();
    } else if (!query.next()) {
        qDebug() << "No matching user found.";
    }

    if (query.exec() && query.next()) {
        user.role  = query.value(0).toString();
        user.group = query.value(1).toString();
        // this->hide();

        // if (role == "student") {
        //     (new StudentWindow(user))->show();
        // } else if (role == "teacher") {
        //     (new TeacherWindow(user))->show();
        // } else if (role == "admin") {
        //     (new AdminWindow(user))->show();
        // }
        if (user.role == "student") {
            qDebug() << "LoginWindow::authenticateUser";
            auto* studentWin = new StudentWindow(user);
            studentWin->show();
            // this->close();
        } else if (user.role == "teacher") {
            auto* teacherWin = new TeacherWindow(user);
            teacherWin->show();
            this->close();
        } else if (user.role == "admin") {
            auto* adminWin = new AdminWindow(user);
            adminWin->show();
            this->close();
        }

    } else {
        ui->errorLabel->setText("Неверный логин или пароль.");
    }
}

void LoginWindow::on_registerButton_clicked()
{
    RegisterWindow *regWindow = new RegisterWindow(this);
    regWindow->show();
    this->hide();
}
