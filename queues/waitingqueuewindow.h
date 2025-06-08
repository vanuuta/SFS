// WaitingQueueWindow.h
#pragma once

#include "basequeuewindow.h"
#include "waitingqueue.h"

class WaitingQueueWindow : public BaseQueueWindow
{
    Q_OBJECT
public:
    explicit WaitingQueueWindow(WaitingQueue* queue, QWidget* parent = nullptr)
        : BaseQueueWindow(queue, parent) {}

};
