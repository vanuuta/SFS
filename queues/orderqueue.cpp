// // orderqueue.cpp
// #include "orderqueue.h"
// #include <QSqlRecord>
// #include <QDebug>
// #include <QSqlError>
// OrderQueue::OrderQueue(QWidget* parent) : BaseQueue(parent)
// {
//     model = new QSqlTableModel(this);
//     model->setTable("order_queue");
//     model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//     model->setSort(model->fieldIndex("created_at"), Qt::AscendingOrder); // сортировка по времени создания
//     model->select();
// }

// bool OrderQueue::addRequest(const Request& request)
// {
//     QSqlRecord record = model->record();
//     record.setValue("name", request.m_name);
//     record.setValue("request_type", request.m_type);
//     record.setValue("status", "ожидание");
//     record.setValue("created_at", QDateTime::currentDateTime());

//     if (!model->insertRecord(-1, record)) {
//         qDebug() << "Ошибка вставки записи в order_queue:" << model->lastError().text();
//         return false;
//     }

//     if (!model->submitAll()) {
//         model->revertAll();
//         qDebug() << "Ошибка сохранения order_queue:" << model->lastError().text();
//         return false;
//     }

//     model->select();
//     emit queueUpdated();
//     return true;
// }

// bool OrderQueue::removeRequest(int requestId)
// {
//     for (int row = 0; row < model->rowCount(); ++row) {
//         if (model->record(row).value("id").toInt() == requestId) {
//             model->removeRow(row);
//             if (!model->submitAll()) {
//                 model->revertAll();
//                 return false;
//             }
//             model->select();
//             emit queueUpdated();
//             return true;
//         }
//     }
//     return false;
// }

// void OrderQueue::updateQueue()
// {
//     model->select();
//     emit queueUpdated();
// }

// bool OrderQueue::setRequestStatus(int requestId, const QString& status)
// {
//     for (int row = 0; row < model->rowCount(); ++row) {
//         if (model->record(row).value("id").toInt() == requestId) {
//             model->setData(model->index(row, model->fieldIndex("status")), status);
//             if (!model->submitAll()) {
//                 model->revertAll();
//                 return false;
//             }
//             model->select();
//             emit queueUpdated();
//             return true;
//         }
//     }
//     return false;
// }
