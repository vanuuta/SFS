#pragma once

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "user.h"

class OrderCertificateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrderCertificateWidget(const User& user, QWidget* parent = nullptr);

private slots:
    void sendRequest();

private:
    User user;
    QComboBox* certificateTypeCombo;
    QLineEdit* purposeEdit;
    QPushButton* sendButton;
};
