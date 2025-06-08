// #pragma once

// #include <QWidget>
// #include <QComboBox>
// #include <QPushButton>
// #include <QVBoxLayout>
// #include "../queues/waitingqueuewindow.h"
// #include "../queues/orderqueuewindow.h"
// #include "../queues/livequeuewindow.h"
// #include "../queues/selforganizingqueuewindow.h"

// class QueueManagerWindow : public QWidget {
//     Q_OBJECT

// public:
//     explicit QueueManagerWindow(QWidget* parent = nullptr)
//         : QWidget(parent)
//     {
//         auto* layout = new QVBoxLayout(this);

//         typeCombo = new QComboBox();
//         typeCombo->addItem("Ожидание");
//         typeCombo->addItem("Предварительная запись");
//         typeCombo->addItem("Живая очередь");
//         typeCombo->addItem("Самоорганизующаяся очередь");

//         openButton = new QPushButton("Открыть очередь");

//         layout->addWidget(typeCombo);
//         layout->addWidget(openButton);

//         connect(openButton, &QPushButton::clicked, this, &QueueManagerWindow::openQueueWindow);
//     }

// private slots:
//     void openQueueWindow() {
//         QString type = typeCombo->currentText();
//         WaitingQueue* wq = new WaitingQueue(this);
//         SelfOrganizingQueue* soq = new SelfOrganizingQueue(this);
//         QWidget* window = nullptr;
//         if (type == "Ожидание") {
//             window = new WaitingQueueWindow(wq, this);
//         } else if (type == "Предварительная запись") {
//             window = new OrderQueueWindow();
//         } else if (type == "Живая очередь") {
//             window = new LiveQueueWindow();
//         } else if (type == "Самоорганизующаяся очередь") {
//             window = new SelfOrganizingQueueWindow(soq, this);
//         }

//         if (window) {
//             window->setAttribute(Qt::WA_DeleteOnClose);
//             window->show();
//         }
//     }

// private:
//     QComboBox* typeCombo;
//     QPushButton* openButton;
// };
