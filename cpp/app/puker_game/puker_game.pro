#-------------------------------------------------
#
# Project created by QtCreator 2016-04-13T07:57:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = puker_game
TEMPLATE = app


SOURCES += main.cpp\
    card.cpp \
    puker.cpp \
    game.cpp \
    player.cpp \
    cardsonhand.cpp \
    playerhuman.cpp \
    playerai.cpp \
    gamewindow.cpp \
    playerinfowidget.cpp

HEADERS  += \
    card.h \
    puker.h \
    game.h \
    player.h \
    cardsonhand.h \
    playerhuman.h \
    playerai.h \
    gamewindow.h \
    playerinfowidget.h

FORMS    +=

RESOURCES += \
    res.qrc
