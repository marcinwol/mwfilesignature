include(../defaults.pri)

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TEMPLATE = app

TARGET = mwfilesignature

SOURCES += main.cpp

LIBS += -L../src -lfilesignature

#HEADERS +=

