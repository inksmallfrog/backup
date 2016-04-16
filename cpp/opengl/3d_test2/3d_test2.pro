#-------------------------------------------------
#
# Project created by QtCreator 2016-03-09T19:24:55
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3d_test2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    openglwidget.cpp \
    irenderable.cpp \
    vector3.cpp \
    vertice.cpp \
    vertices.cpp

HEADERS  += mainwindow.h \
    openglwidget.h \
    irenderable.h \
    vector3.h \
    vertice.h \
    vertices.h

FORMS    += mainwindow.ui
