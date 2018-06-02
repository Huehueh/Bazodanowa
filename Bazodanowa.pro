#-------------------------------------------------
#
# Project created by QtCreator 2018-04-22T12:02:51
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bazodanowa
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dbmanager.cpp \
    addcompanydialog.cpp \
    companydialog.cpp \
    salepurchasedelegate.cpp

HEADERS  += mainwindow.h \
    dbmanager.h \
    addcompanydialog.h \
    companydialog.h \
    salepurchasedelegate.h \
    enums.h \
    names.h

FORMS    += mainwindow.ui \
    companydialog.ui \
    addcompanydialog.ui
