#include "studentwindow.h"

StudentWindow::StudentWindow(const User& user, QWidget* parent)
    : QWidget(parent),  ui(new Ui::StudentWindow),  user(user)
{
    ui->setupUi(this);

    // auto* layout = new QVBoxLayout(this);
    setMinimumSize(600, 400);


    // welcomeLabel = new QLabel("Добро пожаловать, " + user.username);
    // layout->addWidget(welcomeLabel);

    // waitingQueueButton = new QPushButton("Очередь ожидания");
    // orderQueueButton = new QPushButton("Очередь по записи");
    // selfOrganizingQueueButton = new QPushButton("Самоорганизующаяся очередь");

    // layout->addWidget(waitingQueueButton);
    // layout->addWidget(orderQueueButton);
    // layout->addWidget(selfOrganizingQueueButton);

    // connect(waitingQueueButton, &QPushButton::clicked, this, &StudentWindow::openWaitingQueue);
    // connect(orderQueueButton, &QPushButton::clicked, this, &StudentWindow::openOrderQueue);
    // connect(selfOrganizingQueueButton, &QPushButton::clicked, this, &StudentWindow::openSelfOrganizingQueue);
}
StudentWindow::~StudentWindow()
{
    delete ui;
}
void StudentWindow::on_WaitingQueuePushButton_clicked() {
    WaitingQueue* wq = new WaitingQueue(this);
    auto wqw = new WaitingQueueWindow(wq, this);
    wqw->show();
}

void StudentWindow::on_SelfOrganizingQueuePushButton_clicked() {
    SelfOrganizingQueue* soq = new SelfOrganizingQueue(this);
    auto soqw = new SelfOrganizingQueueWindow(soq, this);
    soqw->show();
}
void StudentWindow::on_OrderQueuePushButton_clicked() {
    OrderQueue* oq = new OrderQueue(this);
    auto oqw = new OrderQueueWindow(oq, this);
    oqw->show();
}


// //OrderQueue
// void StudentWindow::openWaitingQueue()
// {
//     WaitingQueue* wq = new WaitingQueue(this);
//     qDebug() << "Model OK: " << wq->getModel()->tableName();  // Должно быть "waiting_queue"
//     waitingQueueWindow = new WaitingQueueWindow(wq, this);
//     qDebug() << "before show: ";
//     waitingQueueWindow->show();
//     qDebug() << "after show: ";
// }

// void StudentWindow::openOrderQueue()
// {
//     auto* window = new OrderQueueWindow(this);
//     window->show();
// }

// void StudentWindow::openSelfOrganizingQueue()
// {
//     auto* window = new SelfOrganizingQueueWindow(this);
//     window->show();
// }


// #include "studentwindow.h"
// #include "ui_studentwindow.h"
// #include <QSqlRecord>
// #include <QSqlError>
// #include <QMessageBox>
// #include <QDateTime>
// StudentWindow::StudentWindow(const User& user, QWidget *parent) :
//     QWidget(parent),
//     ui(new Ui::StudentWindow)
// {
//     ui->setupUi(this);
//     setupModel(user);
//     updateView();
// }

// StudentWindow::~StudentWindow()
// {
//     delete ui;
// }

// void StudentWindow::setupModel(const User& user)
// {
//     requestModel = new QSqlTableModel(this);
//     requestModel->setTable("requests");
//     requestModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
//     requestModel->select();
//     ui->tableView->setModel(requestModel);
//     // requestModel->setHeaderData(requestModel->fieldIndex("id"), Qt::Horizontal, "ID");
//     requestModel->setHeaderData(requestModel->fieldIndex("status"), Qt::Horizontal, "Статус");
//     requestModel->setHeaderData(requestModel->fieldIndex("created_at"), Qt::Horizontal, "Время создания");
//     requestModel->setHeaderData(requestModel->fieldIndex("message"), Qt::Horizontal, "Сообщение");
//     ui->lineEditName->setText(user.name);
//     ui->lineEditGroup->setText(user.group.value());
//     ui->lineEditName->setReadOnly(true);

//     // ui->tableView->setColumnWidth(requestModel->fieldIndex("id"), 40);
//     ui->tableView->setColumnWidth(requestModel->fieldIndex("status"), 100);
//     ui->tableView->setColumnWidth(requestModel->fieldIndex("created_at"), 150);
//     ui->tableView->setColumnWidth(requestModel->fieldIndex("message"), 250);


//     ui->tableView->hideColumn(requestModel->fieldIndex("student_id"));
//     ui->tableView->hideColumn(requestModel->fieldIndex("ID"));
//     ui->tableView->hideColumn(requestModel->fieldIndex("department_id"));


//     ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
//     ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
//     ui->tableView->horizontalHeader()->setStretchLastSection(true);
//     // ui->tableView->resizeColumnsToContents();
// }

// void StudentWindow::on_addRequestButton_clicked()
// {
//     QSqlRecord record = requestModel->record();
//     record.setValue("student_id", 1); // заменить на реального пользователя
//     record.setValue("department_id", 1); // по умолчанию
//     record.setValue("message", ui->messageLineEdit->text().trimmed());
//     record.setValue("status", "новая");
//     record.setValue("created_at", QDateTime::currentDateTime().currentDateTimeUtc());


//     if (!requestModel->insertRecord(-1, record)) {
//         QMessageBox::critical(this, "Ошибка", requestModel->lastError().text());
//     } else if (!requestModel->submitAll()) {
//         QMessageBox::critical(this, "Ошибка сохранения", requestModel->lastError().text());
//         requestModel->revertAll();
//     } else {
//         updateView();
//         ui->messageLineEdit->clear();
//     }
// }

// void StudentWindow::on_refreshButton_clicked()
// {
//     updateView();
// }

// void StudentWindow::updateView()
// {
//     requestModel->select();
//     // ui->tableView->resizeColumnsToContents();
// }

