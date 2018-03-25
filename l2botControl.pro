#-------------------------------------------------
#
# Project created by QtCreator 2018-02-16T01:11:14
#
#-------------------------------------------------

QT       += core gui multimedia qml concurrent

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
    bot/botinstance.cpp \
    optionswindow.cpp \
    options.cpp \
    ipcmanager.cpp \
    bot/botmanager.cpp \
    widgets/mapwidget.cpp \
    threads/commandpipeconnectionthread.cpp \
    threads/datamanagmentpipeconnectionthread.cpp \
    misc/utils.cpp \
    threads/bottingthread.cpp \
    widgets/skillwidget.cpp \
    widgets/skilllistwidget.cpp \
    instanceinfo/skillinfo.cpp \
    instanceinfo/instanceinfobank.cpp \
    botcommands/skillusage.cpp \
    dialogs/skillusagedialog.cpp \
    conditions/condition.cpp \
    conditions/relativepointscondition.cpp \
    dialogs/addconditiondialog.cpp \
    widgets/effectwidget.cpp \
    widgets/effectlist.cpp \
    conditions/effectcondition.cpp \
    conditions/botstatecondition.cpp \
    misc/audioplayer.cpp \
    conditions/effectdurationcondition.cpp \
    widgets/conditionwidget.cpp \
    bot/configuration.cpp \
    widgets/mapcontrolswidget.cpp \
    misc/lineagemapcontroller.cpp \
    widgets/actionconfigurationwidget.cpp \
    instanceinfo/geodataregion.cpp \
    instanceinfo/geo/geodatasquare.cpp \
    instanceinfo/geo/geoflatsquare.cpp \
    instanceinfo/geo/geocomplexsquare.cpp \
    instanceinfo/geo/geomultisquare.cpp \
    instanceinfo/geo/multicell.cpp \
    widgets/scriptswidget.cpp \
    scripting/sbot.cpp \
    scripting/scriptingengine.cpp \
    scripting/sconsole.cpp \
    scripting/scriptingthread.cpp \
    bot/gamedatamanager.cpp \
    widgets/itemswidget.cpp \
    instanceinfo/iteminfo.cpp \
    instanceinfo/instanceinfo.cpp \
    botcommands/itemusage.cpp \
    botcommands/usage.cpp \
    dialogs/additemusagedialog.cpp \
    widgets/itemusagewidget.cpp \
    instanceinfo/npcinfo.cpp \
    conditions/targetracecondition.cpp

HEADERS += \
        mainwindow.h \
    botinstancewidget.h \
    dllinjector.h \
    bot/botinstance.h \
    optionswindow.h \
    options.h \
    ipcmanager.h \
    bot/botmanager.h \
    widgets/mapwidget.h \
    threads/commandpipeconnectionthread.h \
    threads/datamanagmentpipeconnectionthread.h \
    misc/utils.h \
    threads/bottingthread.h \
    widgets/skillwidget.h \
    widgets/skilllistwidget.h \
    instanceinfo/skillinfo.h \
    instanceinfo/instanceinfobank.h \
    botcommands/skillusage.h \
    dialogs/skillusagedialog.h \
    conditions/condition.h \
    conditions/relativepointscondition.h \
    dialogs/addconditiondialog.h \
    widgets/effectwidget.h \
    widgets/effectlist.h \
    conditions/effectcondition.h \
    conditions/botstatecondition.h \
    misc/audioplayer.h \
    conditions/effectdurationcondition.h \
    widgets/conditionwidget.h \
    bot/configuration.h \
    widgets/mapcontrolswidget.h \
    misc/lineagemapcontroller.h \
    widgets/actionconfigurationwidget.h \
    instanceinfo/geodataregion.h \
    instanceinfo/geo/geodatasquare.h \
    instanceinfo/geo/geoflatsquare.h \
    instanceinfo/geo/geocomplexsquare.h \
    instanceinfo/geo/geomultisquare.h \
    instanceinfo/geo/multicell.h \
    widgets/scriptswidget.h \
    scripting/sbot.h \
    scripting/scriptingengine.h \
    scripting/sconsole.h \
    scripting/scriptingthread.h \
    bot/gamedatamanager.h \
    widgets/itemswidget.h \
    instanceinfo/iteminfo.h \
    instanceinfo/instanceinfo.h \
    botcommands/itemusage.h \
    botcommands/usage.h \
    dialogs/additemusagedialog.h \
    widgets/itemusagewidget.h \
    instanceinfo/npcinfo.h \
    conditions/targetracecondition.h

FORMS += \
        mainwindow.ui \
    botinstancewidget.ui \
    optionswindow.ui \
    widgets/mapwidget.ui \
    widgets/skillwidget.ui \
    widgets/skilllistwidget.ui \
    dialogs/skillusagedialog.ui \
    dialogs/addconditiondialog.ui \
    widgets/effectwidget.ui \
    widgets/effectlist.ui \
    widgets/conditionwidget.ui \
    widgets/mapcontrolswidget.ui \
    widgets/actionconfigurationwidget.ui \
    widgets/scriptswidget.ui \
    widgets/itemswidget.ui \
    dialogs/additemusagedialog.ui \
    widgets/itemusagewidget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Libs/build-lineageIPC-Desktop_Qt_5_9_2_MSVC2015_32bit-Debug/release/ -llineageIPC
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Libs/build-lineageIPC-Desktop_Qt_5_9_2_MSVC2015_32bit-Debug/debug/ -llineageIPC

INCLUDEPATH += $$PWD/../../Libs/lineageIPC
DEPENDPATH += $$PWD/../../Libs/lineageIPC

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../Libs/build-lineageIPC-Desktop_Qt_5_9_2_MSVC2015_32bit-Debug/release/liblineageIPC.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../Libs/build-lineageIPC-Desktop_Qt_5_9_2_MSVC2015_32bit-Debug/debug/liblineageIPC.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../Libs/build-lineageIPC-Desktop_Qt_5_9_2_MSVC2015_32bit-Debug/release/lineageIPC.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../Libs/build-lineageIPC-Desktop_Qt_5_9_2_MSVC2015_32bit-Debug/debug/lineageIPC.lib
