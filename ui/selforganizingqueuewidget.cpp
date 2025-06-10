#include "selforganizingqueuewidget.h"
#include <QMessageBox>
#include <QLabel>
#include <QHeaderView>
SelfOrganizingQueueWidget::SelfOrganizingQueueWidget(const QString& studentName, QWidget* parent)
    : QWidget(parent), studentName(studentName)
{
    subjectComboBox = new QComboBox();
    joinQueueButton = new QPushButton("Записаться в очередь");
    leaveQueueButton = new QPushButton("Покинуть очередь");
    queueView = new QTableView();

    auto* topLayout = new QHBoxLayout();
    topLayout->addWidget(new QLabel("Предмет:"));
    topLayout->addWidget(subjectComboBox);
    topLayout->addWidget(joinQueueButton);

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(queueView);
    mainLayout->addWidget(leaveQueueButton);

    connect(subjectComboBox, &QComboBox::currentTextChanged, this, [=](const QString& subject){
        setupModel(subject);
    });

    connect(joinQueueButton, &QPushButton::clicked, this, &SelfOrganizingQueueWidget::joinQueue);
    connect(leaveQueueButton, &QPushButton::clicked, this, &SelfOrganizingQueueWidget::leaveQueue);

    loadSubjects(); // из БД
    setupModel(subjectComboBox->currentText());

}

void SelfOrganizingQueueWidget::joinQueue() {
    QString subject = subjectComboBox->currentText();
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM lab_queue WHERE student_name = :name AND subject_name = :subject");
    checkQuery.bindValue(":name", studentName);
    checkQuery.bindValue(":subject", subject);
    checkQuery.exec();
    checkQuery.next();

    if (checkQuery.value(0).toInt() > 0) {
        QMessageBox::information(this, "Очередь", "Вы уже в очереди по этому предмету.");
        return;
    }

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO lab_queue (student_name, subject_name) VALUES (:name, :subject)");
    insertQuery.bindValue(":name", studentName);
    insertQuery.bindValue(":subject", subject);

    if (!insertQuery.exec()) {
        qDebug() << "Ошибка добавления в очередь:" << insertQuery.lastError().text();
    } else {
        model->select(); // Обновить таблицу
        highlightCurrentUser(); // Подсветить
    }
}


void SelfOrganizingQueueWidget::refreshQueue()
{
    queueList->clear();
    const QStringList students = queueModel->getQueue();
    queueList->addItems(students);
}
void SelfOrganizingQueueWidget::loadSubjects()
{
    QSqlQuery query("SELECT name FROM subjects");

    if (!query.exec()) {
        qDebug() << "Ошибка при получении предметов:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QString subjectName = query.value(0).toString();
        subjectComboBox->addItem(subjectName);
    }
}

void SelfOrganizingQueueWidget::setupModel(const QString& subject) {
    model = new QSqlTableModel(this);
    model->setTable("lab_queue");
    // model->setHeaderData(model->fieldIndex("id"), Qt::Horizontal, "ID");
    // model->setHeaderData(model->fieldIndex("subject_name"), Qt::Horizontal, "Предмет");

    model->setHeaderData(model->fieldIndex("student_name"), Qt::Horizontal, "Имя студента");
    model->setHeaderData(model->fieldIndex("timestamp"), Qt::Horizontal, "Время");
    model->setFilter(QString("subject_name = '%1'").arg(subject));
    model->setSort(2, Qt::AscendingOrder);  // по времени
    model->select();

    queueView->setModel(model);
    queueView->hideColumn(model->fieldIndex("id"));
    queueView->hideColumn(model->fieldIndex("subject_name"));

    queueView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    queueView->setSelectionMode(QAbstractItemView::NoSelection);
    queueView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // queueView->horizontalHeader()->setStretchLastSection(true);

    // Подсветка текущего пользователя
    // highlightCurrentUser();
}
void SelfOrganizingQueueWidget::highlightCurrentUser() {
    for (int row = 0; row < model->rowCount(); ++row) {
        QString _studentName = model->data(model->index(row, 1)).toString();
        if (_studentName == studentName) {
            queueView->selectRow(row);
            break;
        }
    }

}
void SelfOrganizingQueueWidget::leaveQueue() {
    QSqlQuery query;
    query.prepare("DELETE FROM lab_queue WHERE student_name = :name AND subject_name = :subject");
    query.bindValue(":name", studentName);  // используем имя текущего пользователя
    // query.bindValue(":subject", subject);
    if (!query.exec()) {
        qDebug() << "Ошибка при удалении из очереди: " << studentName << " "<< query.lastError().text();
    } else {
        model->select(); // обновим таблицу после удаления
    }
}
