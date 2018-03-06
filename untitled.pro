QT += core
QT -= gui

TARGET = untitled
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp
QMAKE_CXXFLAGS += -std=gnu++11



unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += ncurses
