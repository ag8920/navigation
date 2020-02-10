#-------------------------------------------------
#
# Project created by QtCreator 2019-12-12T15:22:34
#
#-------------------------------------------------

QT       += core gui network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = navigation
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

CONFIG += c++11
QMAKE_LFLAGS_RELEASE+= -static -static-libgcc

CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/debug
} else {
    DESTDIR = $$OUT_PWD/release
}
CONFIG(debug, debug|release) {
#QMAKE_POST_LINK = $$(QTDIR)/bin/windeployqt $$OUT_PWD/debug
} else{
QMAKE_POST_LINK = $$(QTDIR)/bin/windeployqt $$OUT_PWD/release
}

#CONFIG(debug, debug|release)
MOC_DIR=moc
RCC_DIR=rcc
UI_DIR=ui
OBJECTS_DIR=obj

SOURCES += \
        gridbuttons/buttongrid.cpp \
        gridbuttons/mbutton.cpp \
        settginsDialog/settingsdialog.cpp \
        comport/comport.cpp \
        comport/portsettings/settingsportdialog.cpp \
        comport/slipprotocol.cpp \
        controltablegrbl.cpp \
        dynamicFont/dynamicfontsizelabel.cpp \
        dynamicFont/dynamicfontsizepushbutton.cpp \
        ledlamp/rgbled.cpp \
        loger/loger.cpp \
        main.cpp \
        mainwindow.cpp \
        outdialog.cpp \
        qcgaugewidget/attitudewidget.cpp \
        qcgaugewidget/compaswidget.cpp \
        qcgaugewidget/qcgaugewidget.cpp \
        qcgaugewidget/speedwiget.cpp \
        tableform.cpp \
        tablepresent.cpp \
        udpdrv.cpp

HEADERS += \
        gridbuttons/buttongrid.h \
        gridbuttons/mbutton.h \
        settginsDialog/settingsdialog.h \
        comport/comport.h \
        comport/portsettings/settingsportdialog.h \
        comport/slipprotocol.h \
        controltablegrbl.h \
        dynamicFont/dynamicfontsizelabel.h \
        dynamicFont/dynamicfontsizepushbutton.h \
        ledlamp/rgbled.h \
        loger/loger.h \
        mainwindow.h \
        outdialog.h \
        qcgaugewidget/attitudewidget.h \
        qcgaugewidget/compaswidget.h \
        qcgaugewidget/qcgaugewidget.h \
        qcgaugewidget/speedwiget.h \
        tableform.h \
        tablepresent.h \
        udpdrv.h

FORMS += \
        settginsDialog/settingsdialog.ui \
        comport/portsettings/settingsportdialog.ui \
        mainwindow.ui \
        outdialog.ui \        
        tableform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
RC_FILE = resources.rc
