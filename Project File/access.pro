#-------------------------------------------------
#
# Project created by QtCreator 2019-05-30T12:12:12
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = access
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        addgroup.cpp \
        attendance.cpp \
        editeach.cpp \
        form.cpp \
        group.cpp \
        history.cpp \
        insidehist.cpp \
        main.cpp \
        mainwindow.cpp \
        teacher.cpp

HEADERS += \
        addgroup.h \
        attendance.h \
        editeach.h \
        form.h \
        group.h \
        history.h \
        insidehist.h \
        mainwindow.h \
        teacher.h

FORMS += \
        addgroup.ui \
        attendance.ui \
        editeach.ui \
        form.ui \
        group.ui \
        history.ui \
        insidehist.ui \
        mainwindow.ui \
        teacher.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
