include(../defaults.pri)

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TEMPLATE = app

TARGET = mwfilesignature

SOURCES += main.cpp \
    filesignature.cpp

LIBS += -L../src -lmwfilesignature

#HEADERS +=

HEADERS += \
    filesignature.h
