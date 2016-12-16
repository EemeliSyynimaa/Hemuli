#-------------------------------------------------
#
# Project created by QtCreator 2016-11-07T15:25:42
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hemuli
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    herobrowser.cpp \
    createhero.cpp \
    hero.cpp

HEADERS  += mainwindow.h \
    herobrowser.h \
    createhero.h \
    hero.h

FORMS    += mainwindow.ui \
    herobrowser.ui \
    createhero.ui

DISTFILES +=
