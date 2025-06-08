#include "livequeue.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

LiveQueue::LiveQueue(QObject* parent) : BaseQueue(parent) {
    model = new QSqlTableModel(this);
}

bool LiveQueue::addRequest(const QString& name, const QString& message) {
    QSqlQuery query;
    query.prepare("INSERT INTO live_queue (name, message, created_at) VALUES (?, ?, datetime('now'))");
    query.addBindValue(name);
    query.addBindValue(message);
    if (!query.exec()) {
        qWarning() << "LiveQueue insert error:" << query.lastError();
        return false;
    }
    emit queueUpdated();
    return true;
}

bool LiveQueue::removeRequest(int requestId) {
    QSqlQuery query;
    query.prepare("DELETE FROM live_queue WHERE id = ?");
    query.addBindValue(requestId);
    if (!query.exec()) {
        qWarning() << "LiveQueue delete error:" << query.lastError();
        return false;
    }
    emit queueUpdated();
    return true;
}

void LiveQueue::configureModel() {
    model->setTable("live_queue");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
}
