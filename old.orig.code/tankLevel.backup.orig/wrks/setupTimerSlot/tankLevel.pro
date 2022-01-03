#-------------------------------------------------
#
# Project created by QtCreator 2014-10-30T21:06:28
#
#-------------------------------------------------

QT       += core gui

TARGET = tankLevel
TEMPLATE = app


SOURCES += main.cpp\
        tanklevel.cpp

# added manually by me
INCLUDEPATH +=/usr/include/qwt
LIBS += -lqwt

HEADERS  += \
    tanklevel.hpp

FORMS    += tanklevel.ui
