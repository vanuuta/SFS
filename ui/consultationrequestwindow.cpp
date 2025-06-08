// ConsultationRequestWindow.cpp
#include "ConsultationRequestWindow.h"

ConsultationRequestWindow::ConsultationRequestWindow(const QString& studentName, QWidget* parent)
    : QWidget(parent), studentName(studentName)
{
    setWindowTitle("Запись на консультацию");
    setMinimumSize(300, 300);

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignTop);

    // Центрирующий макет
    auto* centerLayout = new QVBoxLayout();
    centerLayout->addStretch();

    // Используем QFormLayout для аккуратной таблицы полей
    auto* formLayout = new QFormLayout();
    formLayout->setLabelAlignment(Qt::AlignRight);
    formLayout->setFormAlignment(Qt::AlignCenter);

    teacherBox = new QComboBox();
    subjectBox = new QComboBox();
    dateEdit = new QDateEdit(QDate::currentDate());
    timeEdit = new QTimeEdit(QTime::currentTime());
    submitButton = new QPushButton("Отправить заявку");

    dateEdit->setCalendarPopup(true);

    formLayout->addRow("Преподаватель:", teacherBox);
    formLayout->addRow("Предмет:", subjectBox);
    formLayout->addRow("Дата:", dateEdit);
    formLayout->addRow("Время:", timeEdit);

    // Отдельно кнопка — центрируем её тоже
    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(submitButton);
    buttonLayout->addStretch();

    // Финальное вложение
    auto* formContainer = new QVBoxLayout();
    formContainer->addLayout(formLayout);
    formContainer->addSpacing(10);
    formContainer->addLayout(buttonLayout);

    centerLayout->addLayout(formContainer);
    centerLayout->addStretch();

    mainLayout->addLayout(centerLayout);

    connect(submitButton, &QPushButton::clicked, this, &ConsultationRequestWindow::submitRequest);

    loadTeachers();
    loadSubjects();
}
void ConsultationRequestWindow::loadTeachers()
{
    QSqlQuery query("SELECT name FROM teachers");
    while (query.next()) {
        teacherBox->addItem(query.value(0).toString());
    }
}

void ConsultationRequestWindow::loadSubjects()
{
    QSqlQuery query("SELECT name FROM subjects");
    while (query.next()) {
        subjectBox->addItem(query.value(0).toString());
    }
}

void ConsultationRequestWindow::submitRequest()
{
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO consultation_queue (student_name, teacher_name, subject, date, time)
        VALUES (:student, :teacher, :subject, :date, :time)
    )");
    query.bindValue(":student", studentName);
    query.bindValue(":teacher", teacherBox->currentText());
    query.bindValue(":subject", subjectBox->currentText());
    query.bindValue(":date", dateEdit->date().toString(Qt::ISODate));
    query.bindValue(":time", timeEdit->time().toString("HH:mm"));

    if (!query.exec()) {
        qDebug() << "Ошибка при записи заявки:" << query.lastError().text();
    } else {
        qDebug() << "Заявка успешно отправлена.";
        this->close();
    }
}
