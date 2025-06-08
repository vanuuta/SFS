QT += core gui sql widgets
QT += sql

CONFIG += c++17

SOURCES += main.cpp \
    core/applicationmanager.cpp \
    db/appointment.cpp \
    db/dbmanager.cpp \
    db/queue.cpp \
    db/queuemanager.cpp \
    db/request.cpp \
    db/result.cpp \
    db/student.cpp \
    ui/user.cpp \
    ui/waitingqueuewindow.cpp \
    ui/addrequestdialog.cpp \
    ui/adminwindow.cpp \
    ui/loginwindow.cpp \
    ui/mainwindow.cpp \
    ui/registerwindow.cpp \
    ui/studentwindow.cpp \
    ui/teacherwindow.cpp

HEADERS += \
    core/applicationmanager.h \
    db/appointment.h \
    db/dbmanager.h \
    db/queue.h \
    db/queuemanager.h \
    db/request.h \
    db/result.h \
    db/student.h \
    ui/user.h \
    ui/waitingqueuewindow.h \
    ui/addrequestdialog.h \
    ui/adminwindow.h \
    ui/loginwindow.h \
    ui/mainwindow.h \
    ui/registerwindow.h \
    ui/studentwindow.h \
    ui/teacherwindow.h

FORMS += \
    ui/waitingqueuewindow.ui \
    ui/addrequestdialog.ui \
    ui/adminwindow.ui \
    ui/loginwindow.ui \
    ui/mainwindow.ui \
    ui/registerwindow.ui \
    ui/studentwindow.ui \
    ui/teacherwindow.ui

# RESOURCES += resources/icons.qrc
