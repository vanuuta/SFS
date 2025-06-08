// #ifndef STUDENTWINDOW_H
// #define STUDENTWINDOW_H

// #include <QWidget>
// #include <QSqlTableModel>
#pragma once
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "user.h"
#include "ui_studentwindow.h"
#include "ConsultationRequestWindow.h"
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
    void toggleTheme();

public:
    bool isDark;
private slots:
    void openWaitingQueue();
    void on_WaitingQueuePushButton_clicked();
    void on_SelfOrganizingQueuePushButton_clicked();
    void on_OrderQueuePushButton_clicked();

private:
    ThemeToggleButton* themeToggleButton;
    Ui::StudentWindow *ui;
    User user;
    WaitingQueueWindow*          waitingQueueWindow          = nullptr;
    // LiveQueueWindow*             liveQueueWindow             = nullptr;
    // OrderQueueWindow*            orderQueueWindow            = nullptr;
    // SelfOrganizingQueueWindow*   SelforganizingQueueWindow   = nullptr;
};
