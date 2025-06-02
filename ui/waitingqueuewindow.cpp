#include "waitingqueuewindow.h"
#include "ui_waitingqueuewindow.h"
#include <QStandardItemModel>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QMessageBox>
#include <QDateTime>
WaitingQueueWindow::WaitingQueueWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitingQueueWindow)
{
    ui->setupUi(this);
    setupModel();
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Заполнение ComboBox
    ui->comboBox_type->addItems({"Консультация", "Лабораторная", "Экзамен"});
    QVariant val = model->data(model->index(3, model->fieldIndex("created_at")));
    qDebug() << "FRFRWFRWFW   " << val.toString();  // или toDateTime()

}

WaitingQueueWindow::~WaitingQueueWindow()
{
    delete ui;
    delete model;
}

void WaitingQueueWindow::setupModel()
{
    model = new QSqlTableModel(this);
    model->setTable("waiting_queue");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
}

void WaitingQueueWindow::on_addButton_clicked()
{
    QString name = ui->lineEdit_name->text().trimmed();
    QString type = ui->comboBox_type->currentText();

    if (name.isEmpty()) {
        showStatusMessage("Имя не может быть пустым.");
        return;
    }

    QSqlRecord record = model->record();
    record.setValue("name", name);
    record.setValue("request_type", type);
    record.setValue("created_at", QDateTime::currentDateTime().currentDateTimeUtc());


    if (!model->insertRecord(-1, record)) {
        showStatusMessage("Ошибка вставки: " + model->lastError().text());
        return;
    }

    if (!model->submitAll()) {
        showStatusMessage("Ошибка сохранения: " + model->lastError().text());
        model->revertAll();
    } else {
        model->select();
        ui->lineEdit_name->clear();
        showStatusMessage("Добавлено в очередь.");
    }
}

void WaitingQueueWindow::on_removeButton_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) {
        showStatusMessage("Не выбрана строка для удаления.");
        return;
    }

    model->removeRow(index.row());
    if (!model->submitAll()) {
        showStatusMessage("Ошибка удаления: " + model->lastError().text());
        model->revertAll();
    } else {
        model->select();
        showStatusMessage("Запись удалена.");
    }
}

void WaitingQueueWindow::on_refreshButton_clicked()
{
    model->select();
    showStatusMessage("Обновлено.");
}

void WaitingQueueWindow::showStatusMessage(const QString& message)
{
    ui->statusLabel->setText(message);
}
