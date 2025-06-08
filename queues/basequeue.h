// basequeue.h
#pragma once

#include <QObject>
#include <QSqlTableModel>
#include <QString>

class BaseQueue : public QObject
{
    Q_OBJECT
public:
    explicit BaseQueue(QObject* parent = nullptr) : QObject(parent), model(new QSqlTableModel(this)) {}

    virtual QSqlTableModel* getModel() const { return model; }

    // Настроить модель (таблица, заголовки, отображение и т.д.)
    virtual void configureModel() = 0;

    // Добавить заявку (через имя и сообщение)
    virtual bool addRequest(const QString& name, const QString& message) = 0;

    // Удалить по ID
    virtual bool removeRequest(int requestId) = 0;

signals:
    void queueUpdated();

protected:
    QSqlTableModel* model;
};
