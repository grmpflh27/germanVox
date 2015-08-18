#-------------------------------------------------
#
# Project created by QtCreator 2015-01-26T13:09:26
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = germanVox
TEMPLATE = app


SOURCES += main.cpp \
    voxcard.cpp \
    voxcardsystem.cpp \
    voxUI.cpp \
    voxcardgame.cpp \
    voxwordlistmodel.cpp \
    voxwordtableview.cpp \
    voxspecialchars.cpp \
    voxEditDialog.cpp

HEADERS  += \
    voxConst.h \
    voxcard.h \
    voxcardsystem.h \
    voxUI.h \
    voxcardgame.h \
    voxwordlistmodel.h \
    voxwordtableview.h \
    voxspecialchars.h \
    voxEditDialog.h

FORMS    += \
    voxUI.ui \
    voxspecialchars.ui

RESOURCES += \
    res.qrc
