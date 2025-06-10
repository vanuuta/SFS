#pragma once

#include <QObject>
#include <QStringList>

class SelfOrganizingQueue : public QObject
{
    Q_OBJECT
public:
    explicit SelfOrganizingQueue(QObject* parent = nullptr);

    void addStudent(const QString& name);
    void removeStudent(const QString& name);
    QStringList getQueue() const;
    bool isInQueue(const QString& name) const;

private:
    QStringList queue;
};
