#-------------------------------------------------
#
# Project created by QtCreator 2013-08-25T13:33:51
#
#-------------------------------------------------

QT += widgets core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets core gui

QMAKE_CXXFLAGS += -std=c++11 -Wall

TARGET = 15Game
TEMPLATE = app


SOURCES += main.cpp\
		mainwindow.cpp \
	block.cpp \
	board.cpp \
    cenwidget.cpp \
    global.cpp \
    a_star.cpp

HEADERS  += mainwindow.h \
	block.h \
	board.h \
    cenwidget.h \
    global.h \
    a_star.h

RESOURCES += \
	img.qrc
