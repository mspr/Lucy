#-------------------------------------------------
#
# Project created by QtCreator 2017-05-19T22:03:36
#
#-------------------------------------------------

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = \
	src \
	app \
	tests

app.depends = src
tests.depends = src
