#-------------------------------------------------
#
# Project created by QtCreator 2014-05-07T21:57:25
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = miTrello
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    listatarjeta.cpp \
    tarjeta.cpp \
    board.cpp \
    initwindow.cpp \
    dialog.cpp \
    api_manager.cpp \
    loginwindow.cpp

HEADERS  += mainwindow.h \
    listatarjeta.h \
    tarjeta.h \
    board.h \
    initwindow.h \
    Lista.h \
    Nodo.h \
    dialog.h \
    api_manager.h \
    loginwindow.h

FORMS    += mainwindow.ui \
    initwindow.ui \
    dialog.ui \
    loginwindow.ui

RESOURCES += \
    res.qrc
