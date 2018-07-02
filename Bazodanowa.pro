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
    salepurchasedelegate.cpp \
    contractorsdialog.cpp \
    salepurchasedialog.cpp

HEADERS  += mainwindow.h \
    dbmanager.h \
    addcompanydialog.h \
    salepurchasedelegate.h \
    enums.h \
    columnnames.h \
    names.h \
    contractorsdialog.h \
    salepurchasedialog.h

FORMS    += mainwindow.ui \
    companydialog.ui \
    addcompanydialog.ui \
    contractorsdialog.ui
