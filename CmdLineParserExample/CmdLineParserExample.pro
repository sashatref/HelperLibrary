QT += core
QT -= gui

TARGET = CmdLineParserExample
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

include(../Source/HelperLibrary.pri)
