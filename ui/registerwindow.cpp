#include "registerwindow.h"
#include "ui_registerwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include "studentwindow.h"
#include "teacherwindow.h"
#include "adminwindow.h"

// RegisterWindow::RegisterWindow(QWidget *parent) :
//     QDialog(parent),
//     ui(new Ui::RegisterWindow)
// {
//     ui->setupUi(this);
//     ui->errorLabel->setText("");
// }

RegisterWindow::RegisterWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    ui->ErrorLabel->setText("");
    ui->roleComboBox->addItems({"Студент", "Преподаватель", "Администратор"});
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}


//TODO  сделать проверку не на совпадение имен, а на совпадению ников (Добавить ники)
//TODO  Добавипть хеширование
//TODO  Сделать гуй всех типов пользователей
void RegisterWindow::on_registerButton_clicked()
{
    QString university        = ui->usernameLineEdit->text();
    QString username          = ui->usernameLineEdit->text();
    QString name              = ui->nameLineEdit->text();
    QString surname           = ui->surnameLineEdit->text();
    QString fathers_surname   = ui->fathers_surnameLineEdit->text();
    QString password          = ui->passwordLineEdit->text();
    QString password_2        = ui->passwordLineEdit_2->text();
    QString role              = ui->roleComboBox->currentText();  // студент / преподаватель / админ
    if (role == "Студент")          role = "student";
    if (role == "Администратор")    role = "admin";
    if (role == "Преподаватель")    role = "teacher";

    if (password != password_2)
    {
        ui->ErrorLabel->setText("Пароли не совпадлают");
        return;
    }

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id FROM users WHERE username = :username");
    checkQuery.bindValue(":username", username);
    if (!checkQuery.exec()) {
        ui->ErrorLabel->setText("Ошибка проверки пользователя: " + checkQuery.lastError().text());
        return;
    }

    if (checkQuery.next()) {
        ui->ErrorLabel->setText("Пользователь с таким именем уже существует");
        return;
    }

    QSqlQuery insertQuery;
    insertQuery.prepare(R"(
        INSERT INTO users (username, password, role)
        VALUES (:username, :password, :role)
    )");
    insertQuery.bindValue(":username", username);
    insertQuery.bindValue(":password", password);  // Лучше использовать хэш!
    insertQuery.bindValue(":role", role);

    if (!insertQuery.exec()) {
        ui->ErrorLabel->setText("Ошибка регистрации: " + insertQuery.lastError().text());
        return;
    }
    User user;
    user.username = username;
    user.name     = surname + name + fathers_surname;
    user.password = password;
    ui->ErrorLabel->setText("Успешная регистрация!");
    accept(); // Закрыть окно регистрации, если успешно
    if (role == "student"){
        auto s_w = new StudentWindow(user);
        s_w->show();
    }else if (role == "teacher"){
        auto t_w = new TeacherWindow(user);
        t_w->show();

    }else if (role == "admin"){
        auto a_w = new AdminWindow(user);
        a_w->show();
    }
    // Здесь добавить логику регистрации
}

// void RegisterWindow::on_reg_pushButton_clicked() {}
