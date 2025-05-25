#include "request.h"
#include "dbmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

Request::Request()
    : m_id(-1), m_studentId(-1)
{}

Request::Request(int id, int studentId, const QString& type, const QString& status, const QDateTime& createdAt)
    : m_id(id), m_studentId(studentId), m_type(type), m_status(status), m_createdAt(createdAt)
{}

int Request::id() const {
    return m_id;
}

int Request::studentId() const {
    return m_studentId;
}

QString Request::type() const {
    return m_type;
}

QString Request::status() const {
    return m_status;
}

QDateTime Request::createdAt() const {
    return m_createdAt;
}

void Request::setId(int value) {
    m_id = value;
}

void Request::setStudentId(int value) {
    m_studentId = value;
}

void Request::setType(const QString& value) {
    m_type = value;
}

void Request::setStatus(const QString& value) {
    m_status = value;
}

void Request::setCreatedAt(const QDateTime& value) {
    m_createdAt = value;
}


bool Request::saveToDb() const {
    QSqlQuery query(DBManager::instance().database());
    query.prepare("INSERT INTO requests (student_id, type, status, created_at) VALUES (?, ?, ?, ?)");
    query.addBindValue(m_studentId);
    query.addBindValue(m_type);
    query.addBindValue(m_status);
    query.addBindValue(m_createdAt.toString(Qt::ISODate));

    if (!query.exec()) {
        qWarning() << "Failed to insert request:" << query.lastError().text();
        return false;
    }

    return true;
}

bool Request::updateStatus(int id, const QString& newStatus) {
    QSqlQuery query(DBManager::instance().database());
    query.prepare("UPDATE requests SET status = ? WHERE id = ?");
    query.addBindValue(newStatus);
    query.addBindValue(id);

    if (!query.exec()) {
        qWarning() << "Failed to update status:" << query.lastError().text();
        return false;
    }
    return true;
}

Request Request::getById(int id) {
    QSqlQuery query(DBManager::instance().database());
    query.prepare("SELECT id, student_id, type, status, created_at FROM requests WHERE id = ?");
    query.addBindValue(id);
    query.exec();

    if (query.next()) {
        return Request(
            query.value(0).toInt(),
            query.value(1).toInt(),
            query.value(2).toString(),
            query.value(3).toString(),
            QDateTime::fromString(query.value(4).toString(), Qt::ISODate)
            );
    }
    return Request();
}

QList<Request> Request::getByStudentId(int studentId) {
    QList<Request> list;
    QSqlQuery query(DBManager::instance().database());
    query.prepare("SELECT id, student_id, type, status, created_at FROM requests WHERE student_id = ?");
    query.addBindValue(studentId);
    query.exec();

    while (query.next()) {
        list.append(Request(
            query.value(0).toInt(),
            query.value(1).toInt(),
            query.value(2).toString(),
            query.value(3).toString(),
            QDateTime::fromString(query.value(4).toString(), Qt::ISODate)
            ));
    }
    return list;
}

QList<Request> Request::getByStatus(const QString& status) {
    QList<Request> list;
    QSqlQuery query(DBManager::instance().database());
    query.prepare("SELECT id, student_id, type, status, created_at FROM requests WHERE status = ?");
    query.addBindValue(status);
    query.exec();

    while (query.next()) {
        list.append(Request(
            query.value(0).toInt(),
            query.value(1).toInt(),
            query.value(2).toString(),
            query.value(3).toString(),
            QDateTime::fromString(query.value(4).toString(), Qt::ISODate)
            ));
    }
    return list;
}

bool Request::removeById(int id) {
    QSqlQuery query(DBManager::instance().database());
    query.prepare("DELETE FROM requests WHERE id = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qWarning() << "Failed to delete request:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<Request> Request::getAllFromDb() {
    QList<Request> list;
    QSqlQuery query("SELECT id, student_id, type, status, created_at FROM requests", DBManager::instance().database());

    while (query.next()) {
        list.append(Request(
            query.value(0).toInt(),
            query.value(1).toInt(),
            query.value(2).toString(),
            query.value(3).toString(),
            QDateTime::fromString(query.value(4).toString(), Qt::ISODate)
            ));
    }
    return list;
}
