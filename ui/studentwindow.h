// #ifndef STUDENTWINDOW_H
// #define STUDENTWINDOW_H

// #include <QWidget>
// #include <QSqlTableModel>
#include "user.h"
#include "ui_studentwindow.h"


// namespace Ui {
// class StudentWindow;
// }

// class StudentWindow : public QWidget
// {
//     Q_OBJECT

// public:
//     explicit StudentWindow(const User& user, QWidget *parent = nullptr);
//     ~StudentWindow();

// private slots:
//     void on_addRequestButton_clicked();
//     void on_refreshButton_clicked();

// private:
//     Ui::StudentWindow *ui;
//     QSqlTableModel *requestModel;
//     void setupModel(const User& user);
//     void updateView();
// };

// #endif // STUDENTWINDOW_H
#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "../queues/waitingqueuewindow.h"
#include "../queues/orderqueuewindow.h"
#include "../queues/livequeuewindow.h"
#include "../queues/selforganizingqueuewindow.h"

class StudentWindow : public QWidget
{
    Q_OBJECT
public:
    explicit StudentWindow(const User& user, QWidget* parent = nullptr);
    ~StudentWindow();

    void setup(const User& user);
private slots:
    // void openWaitingQueue();
    // void openOrderQueue();
    // void openSelfOrganizingQueue();

    void on_WaitingQueuePushButton_clicked();
    void on_SelfOrganizingQueuePushButton_clicked();
    void on_OrderQueuePushButton_clicked();

private:
    Ui::StudentWindow *ui;
    User user;
    // QLabel* welcomeLabel;
    // QPushButton* waitingQueueButton;
    // QPushButton* orderQueueButton;
    // QPushButton* selfOrganizingQueueButton;
// private:
    WaitingQueueWindow*          waitingQueueWindow          = nullptr;
    // LiveQueueWindow*             liveQueueWindow             = nullptr;
    // OrderQueueWindow*            orderQueueWindow            = nullptr;
    // SelfOrganizingQueueWindow*   SelforganizingQueueWindow   = nullptr;
};
