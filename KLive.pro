QT += quick network av
CONFIG += c++11


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(QZXing/QZXing.pri)

android:{
    QT += androidextras
}


SOURCES += main.cpp \
    live.cpp \
    NetWork/httpmanager.cpp \
    Global/global.cpp \
    Crypto/AES/aestools.cpp \
    Crypto/AES/Rijndael.cpp \
    Model/model_roomlist.cpp \
    NetWork/networkaccessmanagerfactory.cpp \
    Model/model_roomitem.cpp \
    Model/admodel.cpp \
    NetWork/download.cpp \
    Platfrom/linju.cpp \
    Platfrom/platfrom.cpp \
    Crypto/Rc4/rc4.cpp

RESOURCES += qml.qrc \
    res.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    live.h \
    NetWork/httpmanager.h \
    Global/global.h \
    Crypto/AES/aestools.h \
    Crypto/AES/Rijndael.h \
    Model/model_roomlist.h \
    NetWork/networkaccessmanagerfactory.h \
    Model/model_roomitem.h \
    Model/admodel.h \
    NetWork/download.h \
    Platfrom/linju.h \
    Platfrom/platfrom.h \
    Crypto/Rc4/rc4.h

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/android/libs/libssl.so \
        $$PWD/android/libs/libcrypto.so
}
