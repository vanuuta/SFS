// queue_manager.cpp
#include "queuemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariantMap>
#include <QDebug>

QueueManager::QueueManager(QObject *parent)
    : QObject(parent)
{
    m_db = QSqlDatabase::database(); // получаем текущее подключение
}

bool QueueManager::enqueueStudent(int studentId, int departmentId)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO waiting_queue (student_id, department_id) VALUES (?, ?)");
    query.addBindValue(studentId);
    query.addBindValue(departmentId);

    if (!query.exec()) {
        qWarning() << "Ошибка при добавлении в очередь:" << query.lastError().text();
        return false;
    }
    return true;
}

bool QueueManager::dequeueNextStudent(int departmentId)
{
    QSqlQuery select(m_db);
    select.prepare("SELECT id FROM waiting_queue WHERE department_id = ? AND status = 'ожидание' ORDER BY queued_at LIMIT 1");
    select.addBindValue(departmentId);

    if (!select.exec() || !select.next()) {
        qWarning() << "Нет студентов в очереди";
        return false;
    }

    int entryId = select.value(0).toInt();

    QSqlQuery update(m_db);
    update.prepare("UPDATE waiting_queue SET status = 'обработан' WHERE id = ?");
    update.addBindValue(entryId);
    return update.exec();
}

QList<QVariantMap> QueueManager::getQueue(int departmentId)
{
    QList<QVariantMap> queue;
    QSqlQuery query(m_db);
    query.prepare("SELECT w.id, s.name, w.queued_at FROM waiting_queue w JOIN students s ON s.id = w.student_id WHERE w.department_id = ? AND w.status = 'ожидание' ORDER BY w.queued_at");
    query.addBindValue(departmentId);
    query.exec();

    while (query.next()) {
        QVariantMap row;
        row["id"] = query.value("id");
        row["name"] = query.value("name");
        row["queued_at"] = query.value("queued_at");
        queue.append(row);
    }
    return queue;
}
