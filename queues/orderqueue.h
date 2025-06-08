// // orderqueue.h
// #pragma once

// #include "basequeue.h"
// #include <QSqlTableModel>

// class OrderQueue : public BaseQueue
// {
//     Q_OBJECT
// public:
//     explicit OrderQueue(QWidget* parent = nullptr);

//     bool addRequest(const Request& request) override;
//     bool removeRequest(int requestId) override;
//     void updateQueue() override;

//     // Можно добавить методы для изменения статуса заказа, например:
//     bool setRequestStatus(int requestId, const QString& status);

// private:
//     QSqlTableModel* model;
// };
