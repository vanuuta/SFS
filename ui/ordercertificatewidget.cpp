#include "ordercertificatewidget.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

OrderCertificateWidget::OrderCertificateWidget(const User& user, QWidget* parent)
    : QWidget(parent), user(user)
{
    auto* layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Тип справки:"));
    certificateTypeCombo = new QComboBox();
    certificateTypeCombo->addItems({
        "Военкомат",
        "Налоговая инспекция",
        "Социальный фонд",
        "По месту работы",
        "По месту работы родителей",
        "Справка о стипендии",
        "Другое"
    });
    layout->addWidget(certificateTypeCombo);

    layout->addWidget(new QLabel("Комментарий:"));
    purposeEdit = new QLineEdit();
    layout->addWidget(purposeEdit);

    sendButton = new QPushButton("Отправить запрос");
    layout->addWidget(sendButton);

    connect(sendButton, &QPushButton::clicked, this, &OrderCertificateWidget::sendRequest);
}

void OrderCertificateWidget::sendRequest()
{
    QString certificateType = certificateTypeCombo->currentText();
    QString purpose = purposeEdit->text().trimmed();

    // if (purpose.isEmpty()) {
        // QMessageBox::warning(this, "Ошибка", "Пожалуйста, укажите цель справки.");
        // return;
    // }

    QSqlQuery query;
    query.prepare("INSERT INTO certificate_requests (student_name, certificate_type, purpose) "
                  "VALUES (:student_name, :certificate_type, :purpose)");
    query.bindValue(":student_name", user.username);
    query.bindValue(":certificate_type", certificateType);
    query.bindValue(":purpose", purpose);

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка БД", query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Успешно", "Запрос отправлен.");
    purposeEdit->clear();
}
