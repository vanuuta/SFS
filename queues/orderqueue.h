#pragma once
#include "basequeue.h"

class OrderQueue : public BaseQueue {
    Q_OBJECT
public:
    explicit OrderQueue(QObject* parent = nullptr);

    bool addRequest(const QString& name, const QString& message) override;
    bool removeRequest(int requestId) override;
    void configureModel() override;
};
