// BaseQueueWindow.h
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include <QLabel>
#include "basequeue.h"

class BaseQueueWindow : public QWidget
{
    Q_OBJECT
public:
    explicit BaseQueueWindow(BaseQueue* queue, QWidget* parent = nullptr)
        : QWidget(parent), queue(queue)
    {
        auto* layout = new QVBoxLayout(this);

        nameEdit = new QLineEdit();
        nameEdit->setPlaceholderText("Введите имя");

        messageEdit = new QLineEdit();
        messageEdit->setPlaceholderText("Сообщение (опционально)");

        auto* inputLayout = new QHBoxLayout;
        inputLayout->addWidget(nameEdit);
        inputLayout->addWidget(messageEdit);
        layout->addLayout(inputLayout);

        addButton = new QPushButton("Добавить");
        removeButton = new QPushButton("Удалить выбранное");
        auto* buttonLayout = new QHBoxLayout;
        buttonLayout->addWidget(addButton);
        buttonLayout->addWidget(removeButton);
        layout->addLayout(buttonLayout);

        tableView = new QTableView();
        tableView->setModel(queue->getModel());
        layout->addWidget(tableView);

        connect(addButton, &QPushButton::clicked, this, &BaseQueueWindow::onAddClicked);
        connect(removeButton, &QPushButton::clicked, this, &BaseQueueWindow::onRemoveClicked);
        connect(queue, &BaseQueue::queueUpdated, this, &BaseQueueWindow::refresh);

        queue->configureModel();
        refresh();
    }

protected slots:
    void onAddClicked() {
        QString name = nameEdit->text().trimmed();
        QString msg = messageEdit->text().trimmed();
        if (!queue->addRequest(name, msg))
            return;
        refresh();
    }

    void onRemoveClicked() {
        auto index = tableView->currentIndex();
        if (!index.isValid()) return;
        int id = queue->getModel()->data(queue->getModel()->index(index.row(), 0)).toInt();
        if (!queue->removeRequest(id))
            return;
        refresh();
    }

    void refresh() {
        queue->getModel()->select();
    }

protected:
    QLineEdit* nameEdit;
    QLineEdit* messageEdit;
    QPushButton* addButton;
    QPushButton* removeButton;
    QTableView* tableView;
    BaseQueue* queue;
};
