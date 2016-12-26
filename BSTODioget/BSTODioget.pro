#-------------------------------------------------
#
# Project created by QtCreator 2016-12-22T11:03:34
#
#-------------------------------------------------

QT       += core gui
  QT       +=         network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BSTODioget
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    mytcpserver.cpp \
    mytcpclient.cpp \
    mytcpserver1.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    mytcpserver.h \
    mytcpclient.h \
    mytcpserver1.h

FORMS    += mainwindow.ui \
    dialog.ui
