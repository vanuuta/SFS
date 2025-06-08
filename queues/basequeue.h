// BaseQueue.h
#pragma once

#include <QObject>
#include <QSqlTableModel>

class BaseQueue : public QObject
{
    Q_OBJECT
public:
    explicit BaseQueue(QObject* parent = nullptr)
        : QObject(parent)
    {
        model = new QSqlTableModel(this);
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    }

    virtual void configureModel() = 0;

    QSqlTableModel* getModel() const { return model; }

    virtual bool addRequest(const QString& name, const QString& message = "") = 0;
    virtual bool removeRequest(int requestId) = 0;

signals:
    void queueUpdated();

protected:
    QSqlTableModel* model;
};
