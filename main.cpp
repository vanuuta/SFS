#include <QApplication>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include "ui/mainwindow.h"
#include "ui/loginwindow.h"
#include "db/dbmanager.h"
#include "db/queuemanagerwindow.h"
// #define  Q_DEBUG
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

    QFile light("styles/light.qss");
    QFile dark("styles/dark.qss");
    if (light.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&light);
        QString style = in.readAll();
        a.setStyleSheet(style);
    } else {
        qDebug() << "Не удалось загрузить light.qss";
    }

    // if (dark.open(QFile::ReadOnly | QFile::Text)) {
    //     QTextStream in(&dark);
    //     QString style = in.readAll();
    //     a.setStyleSheet(style);
    // } else {
    //     qDebug() << "Не удалось загрузить dark.qss";
    // }

    if (!DBManager::instance().connect("queue_system.db")) {
        QMessageBox::critical(nullptr, "Ошибка БД", "Не удалось подключиться к базе данных.");
        return -1;
    }
    // DBManager::instance().clearAllTables();
#ifndef Q_DEBUG
    LoginWindow w;
    w.show();
#else
    // WaitingQueueWindow w;
    // w.show();
    User user ("Ivan", "vanuuta", "123");
    AdminWindow w(user);
    w.show();

    auto* manager = new QueueManagerWindow();
    manager->show();

#endif
    return a.exec();
}
