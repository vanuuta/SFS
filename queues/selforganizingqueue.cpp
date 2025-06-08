#include "selforganizingqueue.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

SelfOrganizingQueue::SelfOrganizingQueue(QObject* parent) : BaseQueue(parent) {
    model = new QSqlTableModel(this);
}

bool SelfOrganizingQueue::addRequest(const QString& name, const QString& message) {
    QSqlQuery query;
    query.prepare("INSERT INTO self_organizing_queue (name, message, priority, created_at) VALUES (?, ?, 0, datetime('now'))");
    query.addBindValue(name);
    query.addBindValue(message);
    if (!query.exec()) {
        qWarning() << "SelfOrganizingQueue insert error:" << query.lastError();
        return false;
    }
    emit queueUpdated();
    return true;
}

bool SelfOrganizingQueue::removeRequest(int requestId) {
    QSqlQuery query;
    query.prepare("DELETE FROM self_organizing_queue WHERE id = ?");
    query.addBindValue(requestId);
    if (!query.exec()) {
        qWarning() << "SelfOrganizingQueue delete error:" << query.lastError();
        return false;
    }
    emit queueUpdated();
    return true;
}

void SelfOrganizingQueue::configureModel() {
    model->setTable("self_organizing_queue");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
}
