#-------------------------------------------------
#
# Project created by QtCreator 2015-03-17T18:22:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt
TEMPLATE = app

LIBS += -lgmp -lgmpxx

SOURCES += main.cpp\
		qtview.cpp \
	main_2.cpp \
	Planet.cpp \
	SolarSystem.cpp \
    qtviewctl.cpp \
    Vector.cpp

HEADERS  += qtview.h \
	Planet.h \
	SolarSystem.h \
    qtviewctl.h \
    Vector.h
