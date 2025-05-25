QT += core gui sql widgets
QT += sql

CONFIG += c++17

SOURCES += main.cpp \
    core/applicationmanager.cpp \
    db/appointment.cpp \
    db/dbmanager.cpp \
    db/queue.cpp \
    db/request.cpp \
    db/result.cpp \
    db/student.cpp \
    ui/addrequestdialog.cpp \
    ui/loginwindow.cpp \
    ui/mainwindow.cpp \
    ui/registerwindow.cpp \

HEADERS += \
    core/applicationmanager.h \
    db/appointment.h \
    db/dbmanager.h \
    db/queue.h \
    db/request.h \
    db/result.h \
    db/student.h \
    ui/addrequestdialog.h \
    ui/loginwindow.h \
    ui/mainwindow.h \
    ui/registerwindow.h \

FORMS += \
    ui/addrequestdialog.ui \
    ui/loginwindow.ui \
    ui/mainwindow.ui \
    ui/registerwindow.ui \

# RESOURCES += resources/icons.qrc
