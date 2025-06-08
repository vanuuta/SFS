#include "adminwindow.h"
#include "ui_adminwindow.h"

#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlError>

AdminWindow::AdminWindow(const User& user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this);
    model->setTable("users");
    model->select();

    model->setHeaderData(model->fieldIndex("id"), Qt::Horizontal, "ID");
    model->setHeaderData(model->fieldIndex("username"), Qt::Horizontal, "Имя пользователя");
    model->setHeaderData(model->fieldIndex("password"), Qt::Horizontal, "Пароль");
    model->setHeaderData(model->fieldIndex("role"), Qt::Horizontal, "Роль");

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    ui->labelName->setText(user.name);
    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    ui->roleFilterComboBox->addItems({"Все", "student", "teacher", "admin"});
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_addUserButton_clicked()
{
    AddUserDialog dialog(this);
    connect(&dialog, &AddUserDialog::userAdded, this, [=]() {
        model->select();  // обновим таблицу
    });
    dialog.exec();

}

void AdminWindow::on_deleteUserButton_clicked()
{
    QModelIndex currentIndex = ui->tableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Выбор строки", "Пожалуйста, выберите пользователя для удаления.");
        return;
    }

    int row = currentIndex.row();

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Удаление пользователя",
        "Вы уверены, что хотите удалить этого пользователя?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        model->removeRow(row);

        if (!model->submitAll()) {
            QMessageBox::critical(this, "Ошибка", "Не удалось удалить пользователя: " + model->lastError().text());
            model->revertAll();
        } else {
            model->select();  // обновляем таблицу
        }
    }
}


void AdminWindow::on_saveChangesButton_clicked()
{
    if (!model->submitAll()) {
        QMessageBox::critical(this, "Ошибка сохранения", model->lastError().text());
        model->revertAll();
    } else {
        QMessageBox::information(this, "Успех", "Изменения сохранены.");
    }
}

void AdminWindow::on_roleFilterComboBox_currentIndexChanged(int index)
{
    QString selected = ui->roleFilterComboBox->currentText();
    if (selected == "Все") {
        model->setFilter("");
    } else {
        model->setFilter("role = '" + selected + "'");
    }
    model->select();
}

