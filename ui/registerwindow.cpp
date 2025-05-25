#include "registerwindow.h"
#include "ui_registerwindow.h"
#include <QMessageBox>
#include <QSqlQuery>

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
    ui->errorLabel->setText("");
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::on_registerSubmitButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString role = ui->roleComboBox->currentText();  // студент / преподаватель / админ

    // Здесь добавить логику регистрации
}
