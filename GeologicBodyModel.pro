#-------------------------------------------------
#
# Project created by QtCreator 2017-08-04T15:24:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GeologicBodyModel
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
CONFIG += qwt
DEFINES += QT_DLL QWT_DLL
LIBS += -L"D:/InstallSoftware/Qt5.8.0_MSVC2015_32bit/5.8/msvc2015/lib" -lqwtd
LIBS += -L"D:/InstallSoftware/Qt5.8.0_MSVC2015_32bit/5.8/msvc2015/lib" -lqwt
INCLUDEPATH += D:/InstallSoftware/Qt5.8.0_MSVC2015_32bit/5.8/msvc2015/include/qwt

SOURCES += main.cpp\
        GWModelMainWindow.cpp \
    GWItemDelegate.cpp \
    GWSettingWindow.cpp

HEADERS  += GWModelMainWindow.h \
    GWItemDelegate.h \
    GWSettingWindow.h

FORMS    += GWModelMainWindow.ui \
    GWSettingWindow.ui

RESOURCES += \
    resources.qrc
