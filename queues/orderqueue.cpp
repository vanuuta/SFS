#include "orderqueue.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

OrderQueue::OrderQueue(QObject* parent) : BaseQueue(parent) {
    model = new QSqlTableModel(this);
}

bool OrderQueue::addRequest(const QString& name, const QString& message) {
    QSqlQuery query;
    query.prepare("INSERT INTO order_queue (name, message, created_at) VALUES (?, ?, datetime('now'))");
    query.addBindValue(name);
    query.addBindValue(message);
    if (!query.exec()) {
        qWarning() << "OrderQueue insert error:" << query.lastError();
        return false;
    }
    emit queueUpdated();
    return true;
}

bool OrderQueue::removeRequest(int requestId) {
    QSqlQuery query;
    query.prepare("DELETE FROM order_queue WHERE id = ?");
    query.addBindValue(requestId);
    if (!query.exec()) {
        qWarning() << "OrderQueue delete error:" << query.lastError();
        return false;
    }
    emit queueUpdated();
    return true;
}

void OrderQueue::configureModel() {
    model->setTable("order_queue");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
}
