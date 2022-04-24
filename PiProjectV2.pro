QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    HomeWidget.cpp \
    MainWindow.cpp \
    RainDataChart.cpp \
    SonosWidget.cpp \
    TFCWidget.cpp \
    discordserver.cpp \
    main.cpp

HEADERS += \
    HomeWidget.h \
    MainWindow.h \
    RainDataChart.h \
    SonosWidget.h \
    TFCWidget.h \
    discordserver.h

FORMS += \
    HomeWidget.ui \
    MainWindow.ui \
    SonosWidget.ui \
    TFCWidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
target.path = ~/PiProject/build
!isEmpty(target.path): INSTALLS += target
