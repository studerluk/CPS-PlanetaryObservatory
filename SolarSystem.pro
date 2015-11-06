#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T12:20:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SolarSystem
TEMPLATE = app

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib
LIBS += -lgmp -lgmpxx


SOURCES += main.cpp\
	Planet.cpp \
	SolarSystem.cpp \
	Vector.cpp \
	qtview.cpp \
	qtviewctl.cpp

HEADERS  += Planet.h \
	SolarSystem.h \
	Vector.h \
	qtview.h \
	qtviewctl.h

FORMS    +=
