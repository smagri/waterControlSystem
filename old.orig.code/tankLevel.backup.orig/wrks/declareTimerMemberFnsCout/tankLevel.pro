#-------------------------------------------------
#
# Project created by QtCreator 2014-10-21T23:31:43
#
#-------------------------------------------------

QT       += core gui

TARGET = tankLevel
TEMPLATE = app


SOURCES += main.cpp\
        tankLevel.cpp

HEADERS  += \
    tankLevel.hpp

INCLUDEPATH +=/usr/include/qwt

LIBS += -lqwt

FORMS    += tankLevel.ui
