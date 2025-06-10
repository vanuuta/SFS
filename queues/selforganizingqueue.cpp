#include "selforganizingqueue.h"

SelfOrganizingQueue::SelfOrganizingQueue(QObject* parent)
    : QObject(parent)
{
}

void SelfOrganizingQueue::addStudent(const QString& name)
{
    if (!queue.contains(name))
        queue.append(name);
}

void SelfOrganizingQueue::removeStudent(const QString& name)
{
    queue.removeAll(name);
}

QStringList SelfOrganizingQueue::getQueue() const
{
    return queue;
}

bool SelfOrganizingQueue::isInQueue(const QString& name) const
{
    return queue.contains(name);
}
