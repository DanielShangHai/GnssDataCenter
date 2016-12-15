#-------------------------------------------------
#
# Project created by QtCreator 2016-12-15T12:37:16
#
#-------------------------------------------------

QT       += core
QT     += network
QT       -= gui

TARGET = ListenA
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    mytcpserver.cpp \
    mytcpclient.cpp

HEADERS += \
    mytcpserver.h \
    mytcpclient.h
