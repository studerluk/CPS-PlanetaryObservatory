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


SOURCES += src/main.cpp\
        src/Planet.cpp \
	src/SolarSystem.cpp \
	src/Vector.cpp \
	src/qtview.cpp \
	src/qtviewctl.cpp

HEADERS  += src/Planet.h \
        src/SolarSystem.h \
	src/Vector.h \
	src/qtview.h \
	src/qtviewctl.h

FORMS    +=
