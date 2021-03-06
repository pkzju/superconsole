#-------------------------------------------------
#
# Project created by QtCreator 2014-07-23T11:28:16
#
#-------------------------------------------------

QT       += core gui printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets serialport
} else {
    include($$QTSERIALPORT_PROJECT_ROOT/src/serialport/qt4support/serialport.prf)
}
QT += widgets webkit webkitwidgets
# application name
TARGET = Console

# type
TEMPLATE = app

DEPENDPATH += .
INCLUDEPATH += .

include(./QFramer/QFramer.pri)
include(./canOpen/canopen.pri)
include(./userui/userui.pri)
include(./canDriver/candriver.pri)

# build dir
BuildDir =build_$$QT_VERSION

CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/$$BuildDir/debug
    OBJECTS_DIR = $$PWD/$$BuildDir/debug/.obj
    MOC_DIR = $$PWD/$$BuildDir/debug/.moc
    RCC_DIR = $$PWD/$$BuildDir/debug/.rcc
    UI_DIR = $$PWD/$$BuildDir/debug/.ui
} else {
    DESTDIR = $$PWD/$$BuildDir/release
    OBJECTS_DIR = $$PWD/$$BuildDir/release/.obj
    MOC_DIR = $$PWD/$$BuildDir/release/.moc
    RCC_DIR = $$PWD/$$BuildDir/release/.rcc
    UI_DIR = $$PWD/$$BuildDir/release/.ui
}

# source
SOURCES += \
    dialogs/aboutdialog.cpp \
    dialogs/bgskinpopup.cpp \
    dialogs/settingdialog.cpp \
    functionpages/rightfloatwindow.cpp \
    mainwindow/centerwindow.cpp \
    mainwindow/mainwindow.cpp \
    mainwindow/settingmenu.cpp \
    mainwindow/settingmenucontroller.cpp \
    mainwindow/thememenu.cpp \
    main.cpp \
    functionpages/qssbuilder.cpp \
    lamp/qcw_indicatorlamp.cpp \
    thread/canthread.cpp \
    thread/serialportthread.cpp \
    parser/protocal.cpp

# header
HEADERS  += \
    dialogs/aboutdialog.h \
    dialogs/bgskinpopup.h \
    dialogs/settingdialog.h \
    functionpages/rightfloatwindow.h \
    mainwindow/centerwindow.h \
    mainwindow/mainwindow.h \
    mainwindow/settingmenu.h \
    mainwindow/settingmenucontroller.h \
    mainwindow/thememenu.h \
    functionpages/qssbuilder.h \
    lamp/qcw_indicatorlamp.h \
    thread/canthread.h \
    thread/serialportthread.h \
    parser/protocal.h

# resources
RESOURCES += \
    QFramer.qrc

# QT4.8 applciation icon
contains(QT_MAJOR_VERSION, 4){
    win32{
        RC_FILE = QFramer.rc
    }
}

# QT5 applciation icon
contains(QT_MAJOR_VERSION, 5){
    RC_ICONS = "skin/images/ico.ico"
}
qtHaveModule(QWebView): QT += QWebView

FORMS +=

LIBS += -LC:\Users\pengkang\Desktop\QFramer-my\lib -lControlCAN

INCLUDEPATH +=$$PWD/qwt
CONFIG(debug, debug|release) {
win32:LIBS += -L$$PWD/lib -lqwtd
#win32:QMAKE_POST_LINK = copy /Y ($$PWD/lib/qwtd.dll) $(DESTDIR)
win32:QMAKE_POST_LINK = copy /Y C:\qwt-6.1.2\lib\qwt.dll $(DESTDIR)
}else {
win32:LIBS += -L$$PWD/lib -lqwt
win32:QMAKE_POST_LINK = copy /Y $$PWD\lib\qwt.dll $(DESTDIR)
}
