#-------------------------------------------------
#
# Project created by QtCreator 2016-10-26T19:54:10
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += xml testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KursyWalut1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    downloader.cpp \
    currency.cpp

HEADERS  += mainwindow.h \
    downloader.h \
    currency.h

FORMS    += mainwindow.ui

DISTFILES +=
