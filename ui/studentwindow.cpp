#include "studentwindow.h"
#include "ui_studentwindow.h"
#include <QSqlRecord>
#include <QSqlError>
#include <QMessageBox>

StudentWindow::StudentWindow(const User& user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentWindow)
{
    ui->setupUi(this);
    setupModel(user);
    updateView();
}

StudentWindow::~StudentWindow()
{
    delete ui;
}

void StudentWindow::setupModel(const User& user)
{
    requestModel = new QSqlTableModel(this);
    requestModel->setTable("requests");
    requestModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    requestModel->select();

    ui->lineEditName->setText(user.name);
    ui->tableView->setModel(requestModel);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->resizeColumnsToContents();
}

void StudentWindow::on_addRequestButton_clicked()
{
    QSqlRecord record = requestModel->record();
    record.setValue("student_id", 1); // заменить на реального пользователя
    record.setValue("department_id", 1); // по умолчанию
    record.setValue("message", ui->messageLineEdit->text().trimmed());
    record.setValue("status", "новая");

    if (!requestModel->insertRecord(-1, record)) {
        QMessageBox::critical(this, "Ошибка", requestModel->lastError().text());
    } else if (!requestModel->submitAll()) {
        QMessageBox::critical(this, "Ошибка сохранения", requestModel->lastError().text());
        requestModel->revertAll();
    } else {
        updateView();
        ui->messageLineEdit->clear();
    }
}

void StudentWindow::on_refreshButton_clicked()
{
    updateView();
}

void StudentWindow::updateView()
{
    requestModel->select();
    ui->tableView->resizeColumnsToContents();
}
