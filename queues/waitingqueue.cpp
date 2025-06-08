// WaitingQueue.cpp
#include "waitingqueue.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>
WaitingQueue::WaitingQueue(QObject* parent)
    : BaseQueue(parent)
{
    qDebug() << "WaitingQueue::WaitingQueue";
    model = new QSqlTableModel(this);
    model->setTable("waiting_queue");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
}

bool WaitingQueue::addRequest(const QString& name, const QString& message)
{
    QSqlQuery query;
    query.prepare("INSERT INTO waiting_queue (name, message, created_at) VALUES (?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(message);
    query.addBindValue(QDateTime::currentDateTime().toString(Qt::ISODate));

    if (!query.exec()) {
        qDebug() << "WaitingQueue insert error:" << query.lastError();
        return false;
    }

    emit queueUpdated();
    return true;
}

bool WaitingQueue::removeRequest(int requestId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM waiting_queue WHERE id = ?");
    query.addBindValue(requestId);

    if (!query.exec()) {
        qDebug() << "WaitingQueue delete error:" << query.lastError();
        return false;
    }

    emit queueUpdated();
    return true;
}

void WaitingQueue::configureModel()
{
    QSqlQuery query;
    query.exec(R"(
        CREATE TABLE IF NOT EXISTS waiting_queue (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            message TEXT
        )
    )");

    model->setTable("waiting_queue");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    if (model->lastError().isValid()) {
        qDebug() << "Model error:" << model->lastError().text();
    }
    model->setHeaderData(model->fieldIndex("id"), Qt::Horizontal, "ID");
    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, "Имя");
    model->setHeaderData(model->fieldIndex("message"), Qt::Horizontal, "Сообщение");
    model->setHeaderData(model->fieldIndex("created_at"), Qt::Horizontal, "Создано");
}
