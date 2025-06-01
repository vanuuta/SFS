#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "registerwindow.h"
#include "studentwindow.h"
#include "teacherwindow.h"
#include "adminwindow.h"

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
    query.prepare("SELECT role FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        QString role = query.value(0).toString();
        this->hide();

        if (role == "student") {
            (new StudentWindow())->show();
        } else if (role == "teacher") {
            (new TeacherWindow())->show();
        } else if (role == "admin") {
            (new AdminWindow())->show();
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
