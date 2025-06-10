#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QString>
#include <QComboBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QTableView>
#include <QSqlTableModel>
#include "../queues/selforganizingqueue.h" // Модель очереди

class SelfOrganizingQueueWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SelfOrganizingQueueWidget(const QString& studentName, QWidget* parent = nullptr);
    void setupModel(const QString& subject);
    void highlightCurrentUser();
private slots:
    void joinQueue();
    void leaveQueue();

private:
    QString studentName;
    QListWidget* queueList;
    QPushButton* joinButton;
    QPushButton* leaveButton;
    QPushButton* joinQueueButton;
    QPushButton* leaveQueueButton;

    QComboBox*  subjectComboBox;
    SelfOrganizingQueue* queueModel;
    QSqlTableModel*      model;
    QTableView* queueView;
    void refreshQueue();
    void loadSubjects();

};
