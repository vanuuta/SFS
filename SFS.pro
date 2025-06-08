QT += core gui sql widgets
QT += sql

CONFIG += c++17

SOURCES += main.cpp \
    core/applicationmanager.cpp \
    db/appointment.cpp \
    db/dbmanager.cpp \
    db/queue.cpp \
    db/queuemanager.cpp \
    db/queuemanagerwindow.cpp \
    db/request.cpp \
    db/result.cpp \
    db/student.cpp \
    queues/basequeuewindow.cpp \
    queues/livequeue.cpp \
    queues/livequeuewindow.cpp \
    queues/orderqueuewindow.cpp \
    queues/selforganizingqueue.cpp \
    queues/selforganizingqueuewindow.cpp \
    themetogglebutton.cpp \
    ui/adduserdialog.cpp \
    ui/consultationrequestwindow.cpp \
    ui/user.cpp \
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
    db/queuemanagerwindow.h \
    db/request.h \
    db/result.h \
    db/student.h \
    queues/basequeuewindow.h \
    queues/livequeue.h \
    queues/livequeuewindow.h \
    queues/orderqueuewindow.h \
    queues/selforganizingqueue.h \
    queues/selforganizingqueuewindow.h \
    themetogglebutton.h \
    ui/adduserdialog.h \
    ui/consultationrequestwindow.h \
    ui/user.h \
    ui/addrequestdialog.h \
    ui/adminwindow.h \
    ui/loginwindow.h \
    ui/mainwindow.h \
    ui/registerwindow.h \
    ui/studentwindow.h \
    ui/teacherwindow.h

FORMS += \
    queues/basequeuewindow.ui \
    ui/adduserdialog.ui \
    ui/addrequestdialog.ui \
    ui/adminwindow.ui \
    ui/loginwindow.ui \
    ui/mainwindow.ui \
    ui/registerwindow.ui \
    ui/studentwindow.ui \
    ui/teacherwindow.ui

# Очереди
HEADERS += queues/basequeue.h    \
           queues/waitingqueue.h \
           queues/orderqueue.h   \
           queues/waitingqueuewindow.h
SOURCES += queues/basequeue.cpp \
           queues/waitingqueue.cpp \
           queues/orderqueue.cpp \
           queues/waitingqueuewindow.cpp

FORMS   += queues/waitingqueuewindow.ui \
           queues/orderqueue.ui

# RESOURCES += resources/icons.qrc

RESOURCES += \
    res.qrc
