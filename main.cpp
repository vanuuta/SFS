#include <QApplication>
#include <QMessageBox>
#include "ui/mainwindow.h"
#include "ui/loginwindow.h"
#include "db/dbmanager.h"
#define  Q_DEBUG
#ifdef   Q_DEBUG
    #include "queues/waitingqueuewindow.h"
    #include "ui/teacherwindow.h"
    #include "ui/studentwindow.h"
    #include "ui/adminwindow.h"
    #include "ui/AddUserDialog.h"
#endif
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!DBManager::instance().connect("queue_system.db")) {
        QMessageBox::critical(nullptr, "Ошибка БД", "Не удалось подключиться к базе данных.");
        return -1;
    }
    DBManager::instance().clearAllTables();
#ifndef Q_DEBUG
    LoginWindow w;
    w.show();
#else
    // WaitingQueueWindow w;
    // w.show();
    User user ("Ivan", "vanuuta", "123");
    StudentWindow w(user);
    w.show();

#endif
    return a.exec();
}
