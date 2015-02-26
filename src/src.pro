include(../defaults.pri)

CONFIG   += console

CONFIG   -= app_bundle
CONFIG   -= qt

TEMPLATE = lib

TARGET = filesignature


HEADERS += \
    filesignature.h

SOURCES += \
    filesignature.cpp
