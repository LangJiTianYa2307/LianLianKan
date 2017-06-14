#-------------------------------------------------
#
# Project created by QtCreator 2017-05-30T11:14:55
#
#-------------------------------------------------

QT       += core gui
QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LianLianKan
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp

HEADERS  += mainwindow.h \
    game.h

FORMS    += mainwindow.ui

RESOURCES += \
    image.qrc \
    sound.qrc
