QT += core
QT -= gui

TARGET = untitled
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    door.cpp \
    room.cpp
QMAKE_CXXFLAGS += -std=gnu++11



unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += ncurses


HEADERS += \
    door.h \
    room.h

HEADERS +=

