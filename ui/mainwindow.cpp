#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "db/request.h"
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlQuery>
#include <QMessageBox>
#include <QComboBox>
#include <QFormLayout>
#include <QSqlError>
#include <ui/addrequestdialog.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //connect(ui->addRequestButton, &QPushButton::clicked, this, &MainWindow::on_addRequestButton_clicked);

    requestModel = new QSqlTableModel(this);

    requestModel->setTable("requests"); // имя таблицы в БД
    requestModel->setEditStrategy(QSqlTableModel::OnManualSubmit); // OnFieldChange/OnManualSubmit
    requestModel->select(); // загрузка данных

    // Настройка заголовков (если хочешь)
    requestModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    requestModel->setHeaderData(1, Qt::Horizontal, tr("ФИО"));
    requestModel->setHeaderData(2, Qt::Horizontal, tr("Тип заявки"));
    // ... по числу полей

    // Подключение модели к таблице
    ui->requestsTableView->setModel(requestModel);
    ui->requestsTableView->resizeColumnsToContents();

    // requestModel = new QStandardItemModel(this);
    // requestModel->setHorizontalHeaderLabels(QStringList() << "ID" << "Студент" << "Тип" << "Статус" << "Создано");
    // ui->requestsTableView->setModel(requestModel);
    // ui->requestsTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // ui->requestsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // loadRequests();

    // connect(ui->refreshRequestsButton, &QPushButton::clicked, this, &MainWindow::loadRequests);

}
void MainWindow::on_addRequestButton_clicked()
{
    QSqlQuery q("SELECT * FROM requests");
    while (q.next()) {
        qDebug() << q.value("id").toInt() << q.value("message").toString();
    }

    int newRow = requestModel->rowCount();

    if (!requestModel->insertRow(newRow)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось вставить строку");
        return;
    } else qDebug() << "Добавлена строка";

    // Установка значений
    requestModel->setData(requestModel->index(newRow, requestModel->fieldIndex("student_id")), 1);
    requestModel->setData(requestModel->index(newRow, requestModel->fieldIndex("department_id")), 1);
    requestModel->setData(requestModel->index(newRow, requestModel->fieldIndex("message")), "Пример запроса");
    requestModel->setData(requestModel->index(newRow, requestModel->fieldIndex("status")), "новая");
    // created_at ставится автоматически

    if (!requestModel->submitAll()) {
        QMessageBox::critical(this, "Ошибка сохранения", requestModel->lastError().text());
        requestModel->revertAll();  // Откатим неудачную попытку
    } else {
        requestModel->select();  // Обновим отображение
    }
}

// void MainWindow::on_addRequestButton_clicked()
// {
//     QSqlRecord record = requestModel->record();

//     // Пример заполнения значениями — замени на реальные данные
//     record.setValue("student_id", 1);
//     record.setValue("department_id", 1);
//     record.setValue("message", "Пример запроса");
//     record.setValue("status", "новая");
//     record.setValue("created_at", QDateTime::currentDateTime()); // если поле есть

//     if (!requestModel->insertRecord(-1, record)) {
//         QMessageBox::warning(this, "Ошибка", "Не удалось добавить запись: " + requestModel->lastError().text());
//         return;
//     }

//     if (!requestModel->submitAll()) {
//         QMessageBox::warning(this, "Ошибка", "Ошибка при сохранении: " + requestModel->lastError().text());
//         return;
//     }

//     requestModel->select(); // Обновим таблицу
//     // int row = requestModel->rowCount();
//     // requestModel->insertRow(row);

//     // requestModel->setData(requestModel->index(row, requestModel->fieldIndex("student_id")), 1);
//     // requestModel->setData(requestModel->index(row, requestModel->fieldIndex("department_id")), 1);
//     // requestModel->setData(requestModel->index(row, requestModel->fieldIndex("message")), "Пример запроса");
//     // requestModel->setData(requestModel->index(row, requestModel->fieldIndex("status")), "новая");
//     // requestModel->setData(requestModel->index(row, requestModel->fieldIndex("created_at")), QDateTime::currentDateTime());

//     // if (!requestModel->submitAll()) {
//     //     QMessageBox::warning(this, "Ошибка", "Ошибка при сохранении: " + requestModel->lastError().text());
//     // } else {
//     //     requestModel->select(); // Обновим отображение
//     // }
// }



// void MainWindow::loadRequests() {
//     requestModel->removeRows(0, requestModel->rowCount());

//     const auto requests = Request::getAllFromDb();
//     for (const auto& r : requests) {
//         QList<QStandardItem*> row;
//         row << new QStandardItem(QString::number(r.id()))
//             << new QStandardItem(QString::number(r.studentId()))
//             << new QStandardItem(r.type())
//             << new QStandardItem(r.status())
//             << new QStandardItem(r.createdAt().toString("yyyy-MM-dd HH:mm"));
//         requestModel->appendRow(row);
//     }
// }

// void MainWindow::on_addRequestButton_clicked() {
//     QDialog dialog(this);
//     dialog.setWindowTitle("Добавить заявку");

//     QFormLayout form(&dialog);

//     QLineEdit* studentIdEdit = new QLineEdit(&dialog);
//     QLineEdit* departmentIdEdit = new QLineEdit(&dialog);
//     QLineEdit* messageEdit = new QLineEdit(&dialog);
//     QComboBox* statusCombo = new QComboBox(&dialog);
//     statusCombo->addItems({"новая", "в работе", "выполнена", "отклонена"});

//     form.addRow("ID студента:", studentIdEdit);
//     form.addRow("ID отдела:", departmentIdEdit);
//     form.addRow("Сообщение:", messageEdit);
//     form.addRow("Статус:", statusCombo);

//     QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
//     form.addRow(&buttonBox);

//     connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
//     connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

//     if (dialog.exec() == QDialog::Accepted) {
//         QSqlQuery query;
//         query.prepare(R"(
//             INSERT INTO requests (student_id, department_id, message, status)
//             VALUES (?, ?, ?, ?)
//         )");

//         query.addBindValue(studentIdEdit->text().toInt());
//         query.addBindValue(departmentIdEdit->text().toInt());
//         query.addBindValue(messageEdit->text());
//         query.addBindValue(statusCombo->currentText());

//         if (!query.exec()) {
//             QMessageBox::warning(this, "Ошибка", "Не удалось добавить заявку: " + query.lastError().text());
//         } else {
//             requestModel->select();  // Обновим отображение таблицы
//         }
//     }
// }

// void MainWindow::on_addRequestButton_clicked()
// {
//     // qDebug() << "Нажата кнопка";
//     QSqlRecord record = requestModel->record();

//     // Вставка данных (примеры, ты можешь изменить под ввод из полей)
//     record.setValue("student_id", 1);          // Подставь реальный ID студента
//     record.setValue("department_id", 1);       // Подставь реальный ID отдела
//     record.setValue("message", "Пример запроса");
//     record.setValue("status", "новая");

//     if (!requestModel->insertRecord(-1, record)) {
//         QMessageBox::warning(this, "Ошибка", "Не удалось добавить запись");
//     } else {
//         requestModel->select();  // Обновим таблицу
//     }
// }
// void MainWindow::on_addRequestButton_clicked()
// {
//     QSqlRecord record = requestModel->record();

//     record.setValue("student_id", 1);
//     record.setValue("department_id", 1);
//     record.setValue("message", "Пример запроса");
//     record.setValue("status", "новая");

//     if (!requestModel->insertRecord(-1, record)) {
//         // QMessageBox::warning(this, "Ошибка", "Не удалось добавить запись: " + requestModel->lastError().text());
//         return;
//     }

//     if (!requestModel->submitAll()) {
//         // QMessageBox::warning(this, "Ошибка", "Не удалось сохранить изменения: " + requestModel->lastError().text());
//         requestModel->revertAll(); // Отменяем изменения в модели
//         return;
//     }

//     requestModel->select();
// }

MainWindow::~MainWindow()
{
    //delete ui;
}

// void MainWindow::on_addRequestButton_clicked() {}
