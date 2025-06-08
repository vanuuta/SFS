#pragma once
#include "basequeue.h"

class SelfOrganizingQueue : public BaseQueue {
    Q_OBJECT
public:
    explicit SelfOrganizingQueue(QObject* parent = nullptr);

    bool addRequest(const QString& name, const QString& message) override;
    bool removeRequest(int requestId) override;
    void configureModel() override;
};
