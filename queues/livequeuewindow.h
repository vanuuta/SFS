// livequeuewindow.h
#pragma once
#include "BaseQueueWindow.h"
#include "LiveQueue.h"

class LiveQueueWindow : public BaseQueueWindow {
    Q_OBJECT
public:
    explicit LiveQueueWindow(QWidget* parent = nullptr)
        : BaseQueueWindow(new LiveQueue(), parent)
    {
        setWindowTitle("Живая очередь");
    }
};
