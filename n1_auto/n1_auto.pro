#-------------------------------------------------
#
# Project created by QtCreator 2016-09-19T13:43:17
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = n1_auto
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mythread.cpp \
    n1_devicetable.cpp \
    handlethread.cpp \
    dev_manage.cpp

HEADERS  += mainwindow.h \
    mythread.h \
    n1_data_typedef.h \
    n1_devicetable.h \
    handlethread.h \
    dev_manage.h

FORMS    += mainwindow.ui \
    n1_devicetable.ui

DISTFILES += \
    readme
