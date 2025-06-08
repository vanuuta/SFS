#pragma once
#include "basequeue.h"

class WaitingQueue : public BaseQueue {
    Q_OBJECT
public:
    explicit WaitingQueue(QObject* parent = nullptr);

    bool addRequest(const QString& name, const QString& message) override;
    bool removeRequest(int requestId) override;
    void configureModel() override;

};
