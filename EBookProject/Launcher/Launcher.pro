#-------------------------------------------------
#
# Project created by QtCreator 2018-09-05T09:42:50
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Launcher
TEMPLATE = app


INCLUDEPATH +=$$PWD main
include(main/main.pri)

INCLUDEPATH+=$$PWD DataBase
include(DataBase/DataBase.pri)

INCLUDEPATH+=$$PWD HomePage
include(HomePage/HomePage.pri)

INCLUDEPATH+=$$PWD BookShelf
include(BookShelf/BookShelf.pri)

INCLUDEPATH+=$$PWD ThirdApp
include(ThirdApp/ThirdApp.pri)

INCLUDEPATH+=$$PWD Utils
include(Utils/Utils.pri)

INCLUDEPATH+=$$PWD Application
include(Application/Application.pri)

INCLUDEPATH+=$$PWD DataItem
include(DataItem/DataItem.pri)





win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/release/ -lPinyinIM
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/debug/ -lPinyinIM
else:unix: LIBS += -L$$PWD/libs/ -lPinyinIM

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/release/ -lSysSettings
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/debug/ -lSysSettings
else:unix: LIBS += -L$$PWD/libs/ -lSysSettings

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs

RESOURCES += \
    pics.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/release/ -lStatusBar
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/debug/ -lStatusBar
else:unix: LIBS += -L$$PWD/libs/ -lStatusBar

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs
