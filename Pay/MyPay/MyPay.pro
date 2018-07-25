#-------------------------------------------------
#
# Project created by QtCreator 2018-05-19T01:40:44
#
#-------------------------------------------------

QT       += network sql websockets

QT       -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

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
    wechat.cpp \
    NetManager/httpmanager.cpp \
    NetManager/cookiejar.cpp \
    SqlManager/sqlmanager.cpp \
    userpay.cpp \
    pay.cpp \
    main.cpp \
    NetManager/websocket.cpp

HEADERS += \
    wechat.h \
    NetManager/httpmanager.h \
    NetManager/cookiejar.h \
    SqlManager/sqlmanager.h \
    userpay.h \
    pay.h \
    NetManager/websocket.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
