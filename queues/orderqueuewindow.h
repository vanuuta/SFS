#pragma once
#include "BaseQueueWindow.h"
#include "OrderQueue.h"

class OrderQueueWindow : public BaseQueueWindow {
    Q_OBJECT
public:
    explicit OrderQueueWindow(OrderQueue* queue, QWidget* parent = nullptr)
        : BaseQueueWindow(queue, parent)
    {
        setWindowTitle("Очередь по записи");
    }
};
