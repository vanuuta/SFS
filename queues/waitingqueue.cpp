// // waitingqueue.cpp
// #include "waitingqueue.h"
// #include <QSqlRecord>

// WaitingQueue::WaitingQueue(QWidget* parent) : BaseQueue(parent)
// {
//     model = new QSqlTableModel(this);
//     model->setTable("waiting_queue");
//     model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//     model->select();
// }

// bool WaitingQueue::addRequest(const Request& request)
// {
//     QSqlRecord record = model->record();
//     record.setValue("name", request.m_name);
//     record.setValue("request_type", request.m_type);
//     // Можно заполнить остальные поля

//     if (!model->insertRecord(-1, record)) {
//         return false;
//     }

//     if (!model->submitAll()) {
//         model->revertAll();
//         return false;
//     }

//     model->select();
//     emit queueUpdated();
//     return true;
// }

// bool WaitingQueue::removeRequest(int requestId)
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

// void WaitingQueue::updateQueue()
// {
//     model->select();
//     emit queueUpdated();
// }
