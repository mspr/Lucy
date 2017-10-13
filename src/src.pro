#-------------------------------------------------
#
# Project created by QtCreator 2017-05-19T22:03:36
#
#-------------------------------------------------

QT += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lucy
TEMPLATE = lib
DESTDIR = ./

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../defaults.pri)
include(output/output.pri)
include(main_view/main_view.pri)
include(tree_view/tree_view.pri)
include(tree_query/tree_query.pri)
include(business/business.pri)
include(project/project.pri)
include(commands/commands.pri)

SOURCES += \
   messagehandler.cpp \
   databasemanager.cpp \
   application.cpp

HEADERS += \
   messagehandler.h \
   databasemanager.h \
   application.h

RESOURCES += \
   resources.qrc
