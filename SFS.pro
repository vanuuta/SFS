QT += core gui sql widgets

CONFIG += c++17

SOURCES += main.cpp \
    core/applicationmanager.cpp \
    db/appointment.cpp \
    db/dbmanager.cpp \
    db/queue.cpp \
    db/request.cpp \
    db/result.cpp \
    db/student.cpp \
    ui/mainwindow.cpp \
    # ...

HEADERS += \
    core/applicationmanager.h \
    db/appointment.h \
    db/dbmanager.h \
    db/queue.h \
    db/request.h \
    db/result.h \
    db/student.h \
    ui/mainwindow.h \
    # ...

FORMS += \
    ui/mainwindow.ui \
    # ...

# RESOURCES += resources/icons.qrc
