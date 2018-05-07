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

<<<<<<< HEAD
HEADERS += \
    door.h \
    room.h
=======
HEADERS +=
>>>>>>> 689e8f23071ece86309ddd5df645f15f272b7b76
