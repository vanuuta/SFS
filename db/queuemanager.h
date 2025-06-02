#pragma once
#include <QObject>
#include <QSqlDatabase>

class QueueManager : public QObject
{
    Q_OBJECT
public:
    explicit QueueManager(QObject *parent = nullptr);

    bool enqueueStudent(int studentId, int departmentId);
    bool dequeueNextStudent(int departmentId);
    QList<QVariantMap> getQueue(int departmentId);

private:
    QSqlDatabase m_db;
};
