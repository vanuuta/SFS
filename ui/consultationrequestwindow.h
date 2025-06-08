// ConsultationRequestWindow.h
#pragma once

#include <QWidget>
#include <QComboBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFormLayout>

class ConsultationRequestWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ConsultationRequestWindow(const QString& studentName, QWidget* parent = nullptr);

private slots:
    void submitRequest();
private:
    void loadTeachers();
    void loadSubjects();
private:
    QString studentName;
    QComboBox* teacherBox;
    QComboBox* subjectBox;
    QDateEdit* dateEdit;
    QTimeEdit* timeEdit;
    QPushButton* submitButton;
};
