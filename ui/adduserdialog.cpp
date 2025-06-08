#include "adduserdialog.h"
#include "ui_adduserdialog.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

AddUserDialog::AddUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserDialog)
{
    ui->setupUi(this);
    ui->labelStatus->clear();
    ui->comboBoxRole->addItems({"student", "teacher", "admin"});
}

AddUserDialog::~AddUserDialog()
{
    delete ui;
}

void AddUserDialog::on_pushButtonAdd_clicked()
{
    QString username = ui->lineEditUsername->text().trimmed();
    QString password = ui->lineEditPassword->text();
    QString role = ui->comboBoxRole->currentText();

    if (username.isEmpty() || password.isEmpty()) {
        ui->labelStatus->setText("Поля не должны быть пустыми");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password, role) VALUES (?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(role);

    if (!query.exec()) {
        ui->labelStatus->setText("Ошибка: " + query.lastError().text());
        return;
    }

    emit userAdded();  // уведомим, что пользователь добавлен
    accept();          // закроем окно
}
