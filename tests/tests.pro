#-------------------------------------------------
#
# Project created by QtCreator 2015-10-01T21:32:11
#
#-------------------------------------------------

include(../defaults.pri)
include(project/project.pri)

TEMPLATE = app

QT += testlib

CONFIG += testcase
CONFIG -= app_bundle

LIBS += -L../src -lLucy

SOURCES += \
   main.cpp

HEADERS += \
