#include "teacherwindow.h"
#include "ui_teacherwindow.h"
#include <QSqlRecord>
#include <QMessageBox>

TeacherWindow::TeacherWindow(const User& user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeacherWindow)
{
    ui->setupUi(this);

    setupModel(user);

    ui->tableView->setModel(requestModel);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    ui->filterComboBox->addItems({"все", "новая", "принята", "выполнена"});
}

void TeacherWindow::setupModel(const User& user)
{
    ui->lineEditName->setText(user.name);
    requestModel = new QSqlTableModel(this);
    requestModel->setTable("requests");
    requestModel->select();
    requestModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

void TeacherWindow::updateFilter()
{
    QString status = ui->filterComboBox->currentText();
    if (status == "все") {
        requestModel->setFilter("");
    } else {
        requestModel->setFilter(QString("status = '%1'").arg(status));
    }
    requestModel->select();
}

void TeacherWindow::on_filterComboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    updateFilter();
}

void TeacherWindow::on_updateStatusButton_clicked()
{
    QModelIndex currentIndex = ui->tableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Выберите строку");
        return;
    }

    int row = currentIndex.row();
    QString newStatus = ui->statusComboBox->currentText();
    QString comment = ui->textEditComment->toPlainText();

    requestModel->setData(requestModel->index(row, requestModel->fieldIndex("status")), newStatus);
    requestModel->setData(requestModel->index(row, requestModel->fieldIndex("comment")), comment);

    if (!requestModel->submitAll()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось обновить запрос");
        requestModel->revertAll();
    } else {
        requestModel->select();
    }
}

TeacherWindow::~TeacherWindow()
{
    delete ui;
}
