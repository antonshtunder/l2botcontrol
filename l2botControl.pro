#-------------------------------------------------
#
# Project created by QtCreator 2018-02-16T01:11:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = l2botControl
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    botinstancewidget.cpp \
    dllinjector.cpp \
    botinstance.cpp \
    optionswindow.cpp \
    options.cpp \
    ipcmanager.cpp \
    botmanager.cpp \
    widgets/mapwidget.cpp \
    threads/commandpipeconnectionthread.cpp \
    threads/datamanagmentpipeconnectionthread.cpp \
    misc/lineagepainter.cpp \
    misc/utils.cpp \
    threads/bottingthread.cpp \
    widgets/skillwidget.cpp \
    widgets/skilllistwidget.cpp \
    instanceinfo/skillinfo.cpp \
    instanceinfo/instanceinfobank.cpp \
    botcommands/skillusage.cpp

HEADERS += \
        mainwindow.h \
    botinstancewidget.h \
    dllinjector.h \
    botinstance.h \
    optionswindow.h \
    options.h \
    ipcmanager.h \
    botmanager.h \
    widgets/mapwidget.h \
    threads/commandpipeconnectionthread.h \
    threads/datamanagmentpipeconnectionthread.h \
    misc/lineagepainter.h \
    misc/utils.h \
    threads/bottingthread.h \
    widgets/skillwidget.h \
    widgets/skilllistwidget.h \
    instanceinfo/skillinfo.h \
    instanceinfo/instanceinfobank.h \
    botcommands/skillusage.h

FORMS += \
        mainwindow.ui \
    botinstancewidget.ui \
    optionswindow.ui \
    widgets/mapwidget.ui \
    widgets/skillwidget.ui \
    widgets/skilllistwidget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libs/build-lineageIPC-Desktop_Qt_5_9_2_MSVC2015_32bit-Debug/release/ -llineageIPC
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libs/build-lineageIPC-Desktop_Qt_5_9_2_MSVC2015_32bit-Debug/debug/ -llineageIPC

INCLUDEPATH += $$PWD/../../Libs/lineageIPC
DEPENDPATH += $$PWD/../../Libs/lineageIPC

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../Libs/build-lineageIPC-Desktop_Qt_5_9_2_MSVC2015_32bit-Debug/release/liblineageIPC.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../Libs/build-lineageIPC-Desktop_Qt_5_9_2_MSVC2015_32bit-Debug/debug/liblineageIPC.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../Libs/build-lineageIPC-Desktop_Qt_5_9_2_MSVC2015_32bit-Debug/release/lineageIPC.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../Libs/build-lineageIPC-Desktop_Qt_5_9_2_MSVC2015_32bit-Debug/debug/lineageIPC.lib
