QT += core gui

TARGET = GetJPG
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

INCLUDEPATH += F:/3rd_Library/GDAL/include

LIBS += F:/3rd_Library/GDAL/lib/gdal_i.lib
