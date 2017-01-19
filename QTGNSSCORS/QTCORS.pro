#-------------------------------------------------
#
# Project created by QtCreator 2017-01-10T15:46:11
#
#-------------------------------------------------

QT       += core gui
QT       +=         network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTCORS
TEMPLATE = app


SOURCES += main.cpp\
        gnssmanagement.cpp \
    clientmanage.cpp \
    newclient.cpp \
    Differsourcetable.cpp \
    basestation.cpp \
    ADDBaseStationDialog.cpp

HEADERS  += gnssmanagement.h \
    clientmanage.h \
    newclient.h \
    Differsourcetable.h \
    basestation.h \
    ADDBaseStationDialog.h

FORMS    += gnssmanagement.ui \
    ADDBaseStationDialog.ui
