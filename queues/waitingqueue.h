#pragma once

#include "BaseQueue.h"
#include <QDateTime>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

class WaitingQueue : public BaseQueue
{
    Q_OBJECT
public:
    explicit WaitingQueue(QObject* parent = nullptr) : BaseQueue(parent) {}

    void configureModel() override {
        model->setTable("waiting_queue");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();

        // Установка заголовков
        model->setHeaderData(model->fieldIndex("id"), Qt::Horizontal, "ID");
        model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, "Имя");
        model->setHeaderData(model->fieldIndex("message"), Qt::Horizontal, "Сообщение");
        model->setHeaderData(model->fieldIndex("created_at"), Qt::Horizontal, "Время создания");
    }

    bool addRequest(const QString& name, const QString& message = "") override {
        if (name.isEmpty()) return false;

        QSqlRecord record = model->record();
        record.setValue("name", name);
        record.setValue("message", message);
        record.setValue("created_at", QDateTime::currentDateTime());

        if (!model->insertRecord(-1, record)) {
            qWarning() << "Ошибка вставки:" << model->lastError().text();
            return false;
        }

        if (!model->submitAll()) {
            qWarning() << "Ошибка сохранения:" << model->lastError().text();
            model->revertAll();
            return false;
        }

        emit queueUpdated();
        return true;
    }

    bool removeRequest(int requestId) override {
        for (int row = 0; row < model->rowCount(); ++row) {
            int id = model->data(model->index(row, model->fieldIndex("id"))).toInt();
            if (id == requestId) {
                model->removeRow(row);
                if (!model->submitAll()) {
                    qWarning() << "Ошибка удаления:" << model->lastError().text();
                    model->revertAll();
                    return false;
                }
                emit queueUpdated();
                return true;
            }
        }
        return false;
    }
};
