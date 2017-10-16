#-------------------------------------------------
#
# Project created by QtCreator 2017-08-06T00:19:12
#
#-------------------------------------------------

QT       += core gui sql xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WeChat
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


SOURCES += main.cpp\
    user.cpp \
    msg.cpp \
    logindialog.cpp \
    dialog.cpp \
    common.cpp \
    maindialog.cpp \
    utils.cpp \
    contentwidget.cpp \
    basedialog.cpp \
    resizabledialog.cpp \
    closabledialog.cpp \
    userinfodialog.cpp

HEADERS  += \
    user.h \
    msg.h \
    logindialog.h \
    dialog.h \
    common.h \
    maindialog.h \
    utils.h \
    contentwidget.h \
    basedialog.h \
    resizabledialog.h \
    closabledialog.h \
    userinfodialog.h

FORMS    += \
    dialog.ui \
    maindialog.ui \
    contentwidget.ui

ICON = Appicon.icns

RESOURCES += \
    resources.qrc

DISTFILES += \
    skin/login.qss \
    skin/main.qss \
    skin/common.qss
